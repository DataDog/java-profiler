---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 05:50:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 855 |
| Sample Rate | 14.25/sec |
| Health Score | 891% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (5 unique values: 40-48 cores)</summary>

```
1790761522 40
1790761527 40
1790761532 40
1790761537 42
1790761542 42
1790761547 42
1790761552 42
1790761557 44
1790761562 44
1790761567 46
1790761572 46
1790761577 46
1790761582 46
1790761587 46
1790761592 46
1790761597 46
1790761602 48
1790761607 48
1790761612 48
1790761617 48
```
</details>

---

