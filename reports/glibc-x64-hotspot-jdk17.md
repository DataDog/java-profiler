---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 08:29:10 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 7-32 cores)</summary>

```
1791289471 7
1791289476 7
1791289481 7
1791289486 7
1791289491 7
1791289496 7
1791289501 7
1791289506 7
1791289512 7
1791289517 7
1791289522 7
1791289527 7
1791289532 32
1791289537 32
1791289542 32
1791289547 32
1791289552 32
1791289557 32
1791289562 32
1791289567 32
```
</details>

---

