---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 09:29:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 10 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1792761899 96
1792761904 96
1792761909 96
1792761914 96
1792761919 96
1792761924 96
1792761929 96
1792761934 96
1792761939 96
1792761944 96
1792761949 96
1792761954 94
1792761959 94
1792761964 94
1792761969 92
1792761974 92
1792761979 92
1792761984 92
1792761989 92
1792761994 92
```
</details>

---

