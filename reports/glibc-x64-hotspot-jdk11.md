---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:37:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 861 |
| Sample Rate | 14.35/sec |
| Health Score | 897% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 56-71 cores)</summary>

```
1789673425 71
1789673430 71
1789673435 56
1789673440 56
1789673445 56
1789673450 56
1789673455 56
1789673460 57
1789673465 57
1789673470 57
1789673475 57
1789673480 57
1789673485 57
1789673490 57
1789673495 57
1789673500 57
1789673505 57
1789673510 57
1789673515 57
1789673520 58
```
</details>

---

