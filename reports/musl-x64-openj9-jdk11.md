---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 13:05:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 68-80 cores)</summary>

```
1793642460 68
1793642465 76
1793642471 76
1793642476 76
1793642481 76
1793642486 76
1793642491 76
1793642496 76
1793642501 76
1793642506 76
1793642511 76
1793642516 76
1793642521 76
1793642526 80
1793642531 80
1793642536 80
1793642541 80
1793642546 80
1793642551 80
1793642556 80
```
</details>

---

