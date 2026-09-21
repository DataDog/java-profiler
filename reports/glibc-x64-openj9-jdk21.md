---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-20 21:23:21 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1789953480 46
1789953485 46
1789953490 46
1789953495 46
1789953500 46
1789953505 46
1789953510 46
1789953515 46
1789953520 46
1789953525 51
1789953530 51
1789953535 51
1789953540 51
1789953545 51
1789953550 51
1789953555 51
1789953560 51
1789953565 51
1789953570 51
1789953575 51
```
</details>

---

