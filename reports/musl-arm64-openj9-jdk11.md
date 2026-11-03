---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 12:51:40 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
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
1793728045 48
```
</details>

---

