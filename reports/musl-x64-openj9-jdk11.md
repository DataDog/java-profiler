---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 05:23:33 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 23.80/sec |
| Health Score | 1488% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 26.47/sec |
| Health Score | 1654% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 84-91 cores)</summary>

```
1769681890 84
1769681895 84
1769681900 84
1769681905 84
1769681910 84
1769681915 84
1769681920 84
1769681925 84
1769681930 84
1769681935 84
1769681940 84
1769681945 84
1769681950 89
1769681955 89
1769681960 89
1769681965 89
1769681970 89
1769681975 89
1769681980 89
1769681985 89
```
</details>

---

