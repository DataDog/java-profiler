---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-29 05:23:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 419 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 20.43/sec |
| Health Score | 1277% |
| Threads | 8 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1769681870 48
1769681875 48
1769681880 48
1769681885 43
1769681890 43
1769681895 43
1769681900 43
1769681905 43
1769681910 43
1769681915 43
1769681920 43
1769681925 43
1769681930 43
1769681935 43
1769681940 43
1769681945 43
1769681950 43
1769681955 43
1769681960 43
1769681965 43
```
</details>

---

