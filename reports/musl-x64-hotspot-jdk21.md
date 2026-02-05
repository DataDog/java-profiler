---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-04 19:34:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 12 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 70-75 cores)</summary>

```
1770251362 75
1770251367 75
1770251372 75
1770251377 75
1770251382 70
1770251387 70
1770251392 70
1770251397 70
1770251402 70
1770251407 70
1770251412 70
1770251417 70
1770251422 70
1770251427 70
1770251432 70
1770251437 70
1770251442 70
1770251447 70
1770251452 70
1770251457 70
```
</details>

---

