---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 07:14:54 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 27-60 cores)</summary>

```
1790766607 38
1790766612 38
1790766617 38
1790766622 38
1790766627 38
1790766632 38
1790766637 38
1790766642 38
1790766647 38
1790766652 38
1790766657 38
1790766662 60
1790766667 60
1790766672 60
1790766677 60
1790766682 60
1790766687 27
1790766692 27
1790766697 27
1790766702 27
```
</details>

---

