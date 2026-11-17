---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 14:02:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 44-49 cores)</summary>

```
1794941878 47
1794941883 49
1794941888 49
1794941893 44
1794941898 44
1794941903 44
1794941908 44
1794941913 44
1794941918 44
1794941923 46
1794941928 46
1794941933 46
1794941938 46
1794941943 46
1794941948 46
1794941953 46
1794941958 46
1794941963 46
1794941968 46
1794941974 46
```
</details>

---

