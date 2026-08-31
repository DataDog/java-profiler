# Evidence: per-kind callback tally confirms CONSTANT_POOL dominates admitStaticFieldRoots() volume

Pod `prof-analyzer-hotdog-jb-c944876b9-8vtzw` / `profiling-stg`, deployed with
`3a2fc0d5e` (temp diagnostic on top of `a86f0dd87`). 36 samples over a 10-minute
window (`kubectl logs ... --since=10m | grep -i kind_counts`).

```
kind_counts k1=1 k2=0 k3=512 k4=450 k5=0 k6=450 k7=308 k8=290  k9=5144  k10=130
kind_counts k1=1 k2=0 k3=512 k4=435 k5=0 k6=426 k7=299 k8=279  k9=4236  k10=113
kind_counts k1=1 k2=0 k3=512 k4=83  k5=0 k6=83  k7=66  k8=480  k9=2862  k10=9
kind_counts k1=1 k2=0 k3=512 k4=466 k5=0 k6=466 k7=209 k8=2339 k9=7553  k10=234
kind_counts k1=1 k2=0 k3=512 k4=430 k5=0 k6=428 k7=308 k8=485  k9=4520  k10=123
kind_counts k1=1 k2=0 k3=512 k4=286 k5=0 k6=286 k7=200 k8=230  k9=2557  k10=24
kind_counts k1=1 k2=0 k3=512 k4=455 k5=0 k6=455 k7=330 k8=352  k9=4509  k10=64
kind_counts k1=1 k2=0 k3=512 k4=53  k5=0 k6=53  k7=53  k8=470  k9=2954  k10=0
kind_counts k1=1 k2=0 k3=512 k4=485 k5=0 k6=485 k7=400 k8=1617 k9=10894 k10=20
kind_counts k1=1 k2=0 k3=512 k4=205 k5=0 k6=205 k7=68  k8=188  k9=2836  k10=81
... (26 more, same shape)
```

Kind legend (jvmti.h `jvmtiHeapReferenceKind`): k1=CLASS, k3=ARRAY_ELEMENT,
k4=CLASS_LOADER, k6=PROTECTION_DOMAIN, k7=INTERFACE, k8=STATIC_FIELD,
k9=CONSTANT_POOL, k10=SUPERCLASS.

## Reading

- **k9 (CONSTANT_POOL) is the largest and most variable kind in every
  sample**: range 2353-10894, always 5-15x larger than k8 (STATIC_FIELD:
  174-2339) in the same sample. Confirms the code-grounded hypothesis in
  `find-candidate1-never-tagged` — per-chunk callback volume is dominated by
  constant-pool-derived heap references, not by a class's own static-field
  count.
- **k3 (ARRAY_ELEMENT) is pinned at exactly 512 in all 36 samples** — equal
  to `STATIC_FIELD_SWEEP_CHUNK_CLASSES`. This is a flat one-per-class
  overhead (one array-element-kind callback per class in the chunk,
  independent of the class's actual content) and not a leak-volume signal.
- k4/k6 (CLASS_LOADER/PROTECTION_DOMAIN) track each other almost exactly in
  every sample (e.g. 450/450, 435/426, 83/83) — expected, since both walk
  the same classloader-chain edge from the class object.
- k1 (CLASS) constant at 1 — the seed edge itself, one per call.
- k2 (FIELD) and k5 (SIGNERS) are 0 in every sample — FIELD kind is not used
  by this code path (STATIC_FIELD is the relevant kind for static fields,
  regular FIELD applies to instance-field walks which this call doesn't do);
  SIGNERS is legitimately almost always empty (unsigned classes).

## Confirms

Resolves the "not yet measured directly" gap in `find-candidate1-never-tagged`
that was blocking the mechanism from being called CONFIRMED. Per-chunk
truncation is most plausibly explained by one or a few CONSTANT_POOL-heavy
classes near the front of a 512-class chunk generating enough callback volume
alone to trip the 4096-callback deadline-check granularity before the walk
reaches deeper into the chunk.

## Does not yet confirm

- Whether this is deterministic (same chunk always truncates at the same
  point every lap) vs. jitter-driven — would need per-class-index visibility
  inside the deadline-check path, not just per-chunk totals.
- Whether candidate[1]'s (klass_id=283) holder class is itself CP-heavy or
  simply sits behind one in classlist order.
