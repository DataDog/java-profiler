---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 05:52:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 29-31 cores)</summary>

```
1791193595 29
1791193600 29
1791193605 29
1791193610 29
1791193615 29
1791193620 29
1791193625 29
1791193630 29
1791193635 29
1791193640 31
1791193645 31
1791193650 31
1791193655 31
1791193660 31
1791193665 31
1791193671 31
1791193676 31
1791193681 31
1791193686 31
1791193691 31
```
</details>

---

