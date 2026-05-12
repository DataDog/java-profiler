---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-12 05:49:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 57-84 cores)</summary>

```
1778579047 72
1778579052 72
1778579057 84
1778579062 84
1778579067 84
1778579072 84
1778579077 84
1778579082 57
1778579087 57
1778579092 57
1778579097 57
1778579102 65
1778579107 65
1778579112 65
1778579117 65
1778579122 65
1778579127 65
1778579132 65
1778579137 65
1778579142 65
```
</details>

---

