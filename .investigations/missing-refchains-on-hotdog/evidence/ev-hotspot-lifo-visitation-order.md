---
id: ev-hotspot-lifo-visitation-order
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-candidate1-never-tagged]
tags: [hotspot, jvmti, FollowReferences, LIFO, visit-stack, source, holder-fill, reversed]
created: 2026-08-26
updated: 2026-08-26
---

# HotSpot FollowReferences uses LIFO visit_stack — drives reversed holder fill

## Source

`openjdk-jdk21/src/hotspot/share/prims/jvmtiTagMap.cpp`

## The visitation loop (lines 2943-2957)

```cpp
// the heap walk starts with an initial object or the heap roots
if (initial_object().is_null()) {
  // ... root collection ...
} else {
  visit_stack()->push(initial_object()());   // holder array pushed
}

if (is_following_references()) {
  while (!visit_stack()->is_empty()) {
    oop o = visit_stack()->pop();            // LIFO pop
    if (!_bitset.is_marked(o)) {
      if (!visit(o)) {
        break;
      }
    }
  }
}
```

`FollowReferences(initial_object=holder_array)` pushes the holder, then
the while-loop pops **LIFO** (last in, first out).

## Array element iteration (lines 2498-2517)

```cpp
inline bool VM_HeapWalkOperation::iterate_over_array(oop o) {
  objArrayOop array = objArrayOop(o);
  // array reference to its class
  oop mirror = ObjArrayKlass::cast(array->klass())->java_mirror();
  if (!CallbackInvoker::report_class_reference(o, mirror)) return false;
  // iterate over the array and report each reference to a non-null element
  for (int index=0; index<array->length(); index++) {
    oop elem = array->obj_at(index);
    if (elem == nullptr) continue;
    if (!CallbackInvoker::report_array_element_reference(o, elem, index)) return false;
  }
  return true;
}
```

`visit(holder)` calls `iterate_over_array`, which reports elements
0..n-1 in order via `report_array_element_reference`. Each reported
element that the callback returns `JVMTI_VISIT_OBJECTS` for gets
`check_for_visit()` → `visit_stack()->push(elem)` (line 1462):

```cpp
static inline bool check_for_visit(oop obj) {
  if (!_bitset->is_marked(obj)) visit_stack()->push(obj);
  return true;
}
```

So elements are **pushed in index order 0..n-1**, but the while-loop
**pops LIFO** — meaning the class at `holder[n-1]` is descended first,
`holder[0]` last.

## Consequence for admitStaticFieldRoots()

If the holder is filled as `holder[i] = classes[chunk_start + i]`
(ascending), LIFO descent visits classes in **reverse** order
(chunk_end-1 first, chunk_start last). An abort at class p means the
*done* set is {p+1..chunk_end-1} and the *pending* set is
{chunk_start..p-1} — so "resume at last seen" would skip the pending
low-index classes.

**Fix:** fill the holder in **reversed** order:
`holder[i] = classes[chunk_end - 1 - i]`. Then LIFO pop visits
`holder[n-1] = classes[chunk_start]` first → **ascending original index
order**. An abort at class p now means done={chunk_start..p-1},
partial={p}, pending={p+1..chunk_end-1}. Resume at p (redo the partial
class) — no completed classes re-walked, no pending classes skipped.

## Verification

Read directly from openjdk-jdk21 source at
`/System/Volumes/Data/Users/jaroslav.bachorik/opensource/openjdk/openjdk-jdk21/src/hotspot/share/prims/jvmtiTagMap.cpp`.
No runtime experiment needed — the visitation order is structural in
the C++ code, not configurable or JVM-version-dependent.
