---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-14 10:14:46 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 61 |
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
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 61-81 cores)</summary>

```
1786716532 73
1786716537 73
1786716542 73
1786716547 73
1786716552 81
1786716557 81
1786716562 81
1786716567 81
1786716572 81
1786716577 81
1786716582 81
1786716587 61
1786716592 61
1786716597 61
1786716602 61
1786716607 61
1786716612 61
1786716617 61
1786716622 61
1786716627 61
```
</details>

---

