---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 09:39:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 12 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794926017 51
1794926022 51
1794926027 51
1794926032 51
1794926037 51
1794926042 51
1794926047 51
1794926052 51
1794926057 51
1794926062 51
1794926067 51
1794926072 51
1794926077 46
1794926082 46
1794926087 46
1794926092 46
1794926097 46
1794926102 46
1794926107 46
1794926112 46
```
</details>

---

