# Round 13: ground-truth probe for the LEAK_BUFFER wrapper (ev)

Date: 2026-09-15
Context: fix B+C (ccdb03b89) deployed and verified mechanically working on the
pod (prof-analyzer-hotdog-jb-d9d8cf-plwpx, JVM restarted 16:14:50Z), but the
LEAK_BUFFER wrapper still never walks.

## Round 12 observations on the pod (fix B+C live)

- Anchor walks went from budget 4/pass to 635 walks/15 min; 41–100+ distinct
  anchor classes cycled (SynchronizedMap, UnmodifiableSet, ...), collector
  static_anchor_tags=16 + FIFO 16 = 32/pass as designed.
- 5843 root-attached STATIC_FIELD first-admissions logged (JVM fresh → sweep
  admits statics before BFS, unlike the old recording where all sweep k8 hits
  were already-admitted).
- maybeUpgradeRootAttachedRootKind 9→8 upgrades firing.
- Leak rebuilding fast ("allocated 75 MB, retained chunks 9→13, heap 23-25%").
- **NO `SynchronizedRandomAccessList` walk ever, zero interception, zero
  ReferenceChain events, and zero com/dd/profiling app classes among walked
  anchors.**

## Deduction chain (why the probe was needed)

`klass_id` in every log (admit / sweep-hit / push / upgrade) is the object's
**own** class id — `class_tag` in heapReferenceCallback params is the REFEREE's
class; the variable named `referrer_klass` is misnamed. All logs share one id
space; only the walk anchor log lacked the id (printed signature only).

Every admission shape for the wrapper should end in a walk log:
- k8 root-attached admit → index → collector walk
- chain-attached → sweep k8 re-hit → pushAtRiskStaticAnchor → FIFO walk
- already-admitted re-hit → maybeUpgrade (parent==0) or push (parent!=0)

None observed → contradiction; deduction exhausted. Also established: the
sweep re-partitions app classes (non-null classloader) to the FRONT every call,
so ProfileAnalyzer's class was swept within the first minute of JVM life, once
per ~70 passes (~30 s) since.

## Round 13 instrumentation (this commit)

1. **LEAK_BUFFER probe** in `admitStaticFieldRoots` (before FollowReferences,
   before class-local cleanup): for each chunk class whose signature contains
   `ProfileAnalyzer`, GetStaticFieldID("LEAK_BUFFER", "Ljava/util/List;")
   (descriptor confirmed from the pod jar bytecode: `strings` on
   ProfileAnalyzer.class shows `LEAK_BUFFER` / `Ljava/util/List;`) →
   GetStaticObjectField → GetTag → frontier lookup → log
   `wrapper_tag / frontier_found / parent / root_kind / state / leak_tag /
   depth / referrer_klass`. Once per sweep chunk containing the holder class.
   Interpretable outcomes:
   - `wrapper_tag=0` persistently → wrapper never admitted at all (find the
     filter that drops it)
   - `frontier_found=0` with tag>0 → tag is not a frontier tag (leak-tag
     range? tag-range bug?)
   - `frontier_found=1 parent=0 root_kind=8` → admitted root-attached but
     never walked → index/collector bug (cross-check with 2.)
   - `frontier_found=1 parent!=0` → chain-attached → FIFO question
2. **klass_id added to walkStaticFieldAnchors anchor log** (entry.referrer_klass
   = own class id): walked anchors now cross-referenceable with sweep/admit/
   push id space. If the wrapper's id (visible in the probe log via
   referrer_klass) appears in sweep hits but never in walk logs → collector
   bug; if never in sweep logs at all → admission bug.

## Verification

- gtestRelease: all ReferenceChainsBfsTest pass; 344 OK; only crash is the
  pre-existing SearchRestartTest.UrgentOOMProjectionBypassesCandidateGate
  SIGSEGV (known on clean HEAD 685f414b1, separate issue).
- spotlessApply clean; buildRelease -Pskip-tests succeeds.

## Next

- NOTE 16:50Z: the old pod (plwpx) was deleted; the replacement
  `prof-analyzer-hotdog-jb-d9d8cf-rz992` (up 16:45Z) is STOCK - no
  `-Ddd.profiling.experimental.ddprof.referencechains.enabled=true` flag,
  stock image `prof-analyzer-hotdog:v137233187-2ad7b593`, zero engine logs.
  The in-pod modifications died with the pod; the deployment spec was never
  patched. User must re-apply their deploy procedure on rz992 (flag + .so
  from b5dd09675 + restart).
- Grep after redeploy: `LEAK_BUFFER probe` (every ~30 s while the holder
  class is in the current chunk), then interpret per the outcome table
  above.
