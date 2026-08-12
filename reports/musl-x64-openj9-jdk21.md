---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:48:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 19-43 cores)</summary>

```
1786527811 22
1786527816 19
1786527821 19
1786527826 19
1786527831 19
1786527836 31
1786527841 31
1786527846 31
1786527851 31
1786527856 31
1786527861 31
1786527866 43
1786527871 43
1786527876 43
1786527881 43
1786527886 43
1786527891 43
1786527896 43
1786527901 43
1786527906 43
```
</details>

---

