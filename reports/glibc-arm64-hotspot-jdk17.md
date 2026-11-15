---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-14 21:04:20 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794708016 48
1794708021 48
1794708026 48
1794708031 43
1794708037 43
1794708042 43
1794708047 43
1794708052 43
1794708057 43
1794708062 43
1794708067 43
1794708072 43
1794708077 43
1794708082 43
1794708087 43
1794708092 43
1794708097 43
1794708102 43
1794708107 43
1794708112 43
```
</details>

---

