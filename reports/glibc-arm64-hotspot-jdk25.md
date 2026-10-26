---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 11:06:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 40-45 cores)</summary>

```
1793026895 40
1793026900 42
1793026905 42
1793026910 45
1793026915 45
1793026920 45
1793026925 45
1793026930 45
1793026935 45
1793026940 45
1793026945 45
1793026950 43
1793026955 43
1793026960 43
1793026965 43
1793026970 43
1793026975 43
1793026980 43
1793026985 43
1793026990 43
```
</details>

---

