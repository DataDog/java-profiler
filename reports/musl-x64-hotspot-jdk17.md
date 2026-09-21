---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:46:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 41-68 cores)</summary>

```
1789980042 41
1789980047 41
1789980052 41
1789980057 41
1789980062 41
1789980067 68
1789980072 68
1789980077 68
1789980082 68
1789980087 68
1789980092 68
1789980097 68
1789980102 68
1789980107 68
1789980112 68
1789980117 68
1789980122 68
1789980127 68
1789980132 68
1789980137 68
```
</details>

---

