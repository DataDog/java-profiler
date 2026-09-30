---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 07:18:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1067 |
| Sample Rate | 17.78/sec |
| Health Score | 1111% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790766839 48
1790766844 48
1790766850 48
1790766855 48
1790766860 48
1790766865 48
1790766870 48
1790766875 48
1790766880 48
1790766885 48
1790766890 48
1790766895 48
1790766900 48
1790766905 48
1790766910 48
1790766915 43
1790766920 43
1790766925 43
1790766930 43
1790766935 43
```
</details>

---

