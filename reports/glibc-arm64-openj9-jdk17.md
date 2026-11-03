---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:51:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 9 |
| Allocations | 137 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1793727945 46
1793727950 46
1793727955 46
1793727960 46
1793727965 46
1793727970 46
1793727975 46
1793727980 46
1793727985 47
1793727990 47
1793727995 47
1793728000 47
1793728005 48
1793728010 48
1793728015 48
1793728020 48
1793728025 48
1793728030 48
1793728035 48
1793728040 48
```
</details>

---

