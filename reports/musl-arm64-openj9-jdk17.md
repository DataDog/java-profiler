---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 20:34:27 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 48-50 cores)</summary>

```
1790209791 48
1790209796 48
1790209801 48
1790209806 50
1790209811 50
1790209816 50
1790209821 50
1790209826 50
1790209831 50
1790209836 50
1790209841 50
1790209846 50
1790209851 50
1790209856 50
1790209861 50
1790209866 50
1790209871 50
1790209876 50
1790209881 50
1790209886 50
```
</details>

---

