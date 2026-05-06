---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 19:44:04 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 48-69 cores)</summary>

```
1778110805 48
1778110810 48
1778110815 48
1778110820 48
1778110825 48
1778110830 50
1778110835 50
1778110840 50
1778110845 50
1778110850 50
1778110855 50
1778110860 50
1778110865 50
1778110870 50
1778110875 50
1778110880 50
1778110885 50
1778110890 69
1778110895 69
1778110900 69
```
</details>

---

