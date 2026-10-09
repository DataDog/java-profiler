---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 07:07:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791543734 43
1791543739 43
1791543744 43
1791543749 43
1791543754 43
1791543759 48
1791543764 48
1791543769 48
1791543774 48
1791543779 48
1791543784 48
1791543789 48
1791543794 48
1791543799 48
1791543804 48
1791543809 48
1791543814 48
1791543819 48
1791543824 48
1791543829 48
```
</details>

---

