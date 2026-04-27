---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-27 04:26:03 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1777278031 30
1777278036 30
1777278041 30
1777278046 30
1777278051 30
1777278056 30
1777278061 32
1777278066 32
1777278071 32
1777278076 32
1777278081 32
1777278086 32
1777278091 32
1777278096 32
1777278101 32
1777278106 32
1777278111 27
1777278116 27
1777278121 27
1777278126 27
```
</details>

---

