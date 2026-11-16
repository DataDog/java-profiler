---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:45:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 12 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (4 unique values: 46-51 cores)</summary>

```
1794840027 46
1794840032 46
1794840037 46
1794840042 46
1794840047 51
1794840052 51
1794840057 49
1794840062 49
1794840067 49
1794840072 49
1794840077 49
1794840082 49
1794840087 49
1794840092 49
1794840097 49
1794840102 49
1794840107 49
1794840112 49
1794840117 49
1794840122 49
```
</details>

---

