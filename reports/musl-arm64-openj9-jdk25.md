---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 14:43:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777487885 64
1777487890 64
1777487895 64
1777487900 64
1777487905 64
1777487910 64
1777487915 64
1777487920 64
1777487925 59
1777487930 59
1777487935 59
1777487940 59
1777487945 59
1777487950 59
1777487955 59
1777487960 59
1777487965 59
1777487970 59
1777487975 59
1777487980 59
```
</details>

---

