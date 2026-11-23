---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:59:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 39-45 cores)</summary>

```
1795431307 39
1795431312 39
1795431317 39
1795431322 39
1795431327 39
1795431332 39
1795431337 45
1795431342 45
1795431347 45
1795431352 43
1795431357 43
1795431362 43
1795431367 43
1795431372 43
1795431377 43
1795431382 43
1795431387 43
1795431392 43
1795431397 43
1795431402 43
```
</details>

---

