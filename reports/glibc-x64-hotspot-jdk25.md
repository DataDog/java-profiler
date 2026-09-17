---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:41:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 78-81 cores)</summary>

```
1789673460 81
1789673465 80
1789673470 80
1789673475 80
1789673480 80
1789673485 80
1789673490 80
1789673495 80
1789673500 80
1789673505 80
1789673510 78
1789673515 78
1789673520 78
1789673525 78
1789673530 78
1789673535 78
1789673540 78
1789673545 78
1789673550 80
1789673555 80
```
</details>

---

