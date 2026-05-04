---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-03 21:21:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 50-54 cores)</summary>

```
1777857364 50
1777857369 50
1777857374 54
1777857379 54
1777857384 54
1777857389 54
1777857394 54
1777857399 54
1777857404 54
1777857409 54
1777857414 54
1777857419 54
1777857424 54
1777857429 54
1777857434 54
1777857439 54
1777857444 54
1777857449 54
1777857454 54
1777857459 54
```
</details>

---

