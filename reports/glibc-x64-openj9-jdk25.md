---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 15:32:42 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 69-75 cores)</summary>

```
1793388545 69
1793388550 69
1793388555 71
1793388560 71
1793388565 73
1793388570 73
1793388575 75
1793388580 75
1793388585 75
1793388590 75
1793388595 75
1793388600 73
1793388605 73
1793388610 73
1793388615 73
1793388620 75
1793388625 75
1793388630 75
1793388635 75
1793388640 75
```
</details>

---

