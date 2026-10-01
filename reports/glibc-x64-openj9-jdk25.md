---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 00:59:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 57-63 cores)</summary>

```
1790830525 63
1790830530 63
1790830535 63
1790830540 63
1790830545 63
1790830550 60
1790830555 60
1790830560 60
1790830565 60
1790830570 60
1790830575 60
1790830580 57
1790830585 57
1790830590 57
1790830595 57
1790830600 57
1790830605 57
1790830610 57
1790830615 57
1790830620 57
```
</details>

---

