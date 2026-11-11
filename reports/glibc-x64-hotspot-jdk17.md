---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:36:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (4 unique values: 61-77 cores)</summary>

```
1794407482 77
1794407487 77
1794407492 77
1794407497 77
1794407502 77
1794407507 77
1794407512 77
1794407517 77
1794407522 77
1794407527 77
1794407532 77
1794407537 77
1794407542 68
1794407547 68
1794407552 70
1794407557 70
1794407562 70
1794407567 70
1794407572 61
1794407577 61
```
</details>

---

