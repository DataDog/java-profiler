---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-25 15:07:39 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (4 unique values: 62-76 cores)</summary>

```
1787684537 62
1787684542 62
1787684547 66
1787684552 66
1787684557 66
1787684562 66
1787684567 66
1787684572 66
1787684577 66
1787684582 66
1787684587 66
1787684592 66
1787684597 66
1787684602 66
1787684607 68
1787684612 68
1787684617 68
1787684622 68
1787684627 68
1787684632 68
```
</details>

---

