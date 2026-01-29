---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 05:23:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 28.20/sec |
| Health Score | 1762% |
| Threads | 11 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1221 |
| Sample Rate | 40.70/sec |
| Health Score | 2544% |
| Threads | 12 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1769681882 36
1769681887 36
1769681892 36
1769681897 36
1769681902 36
1769681907 36
1769681912 36
1769681917 36
1769681922 36
1769681927 36
1769681932 36
1769681937 48
1769681942 48
1769681947 48
1769681952 48
1769681957 48
1769681962 48
1769681967 48
1769681972 48
1769681977 48
```
</details>

---

