---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:58:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 12 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1795431276 57
1795431281 57
1795431286 57
1795431291 57
1795431296 57
1795431301 57
1795431306 57
1795431312 57
1795431317 57
1795431322 55
1795431327 55
1795431332 55
1795431337 55
1795431342 55
1795431347 55
1795431352 55
1795431357 55
1795431362 55
1795431367 55
1795431372 55
```
</details>

---

