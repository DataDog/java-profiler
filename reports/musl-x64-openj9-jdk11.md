---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 05:59:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 41 |
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
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 41-78 cores)</summary>

```
1794912819 78
1794912824 78
1794912829 78
1794912834 78
1794912839 78
1794912844 78
1794912849 78
1794912854 78
1794912859 45
1794912864 45
1794912869 45
1794912874 45
1794912879 61
1794912884 61
1794912889 41
1794912894 41
1794912899 41
1794912904 41
1794912909 41
1794912914 41
```
</details>

---

