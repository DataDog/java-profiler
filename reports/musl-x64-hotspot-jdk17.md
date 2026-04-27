---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 05:15:09 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1777280988 32
1777280993 32
1777280998 32
1777281003 32
1777281008 32
1777281013 32
1777281018 32
1777281023 32
1777281028 32
1777281033 32
1777281038 27
1777281043 27
1777281048 27
1777281053 27
1777281058 27
1777281063 27
1777281068 27
1777281073 22
1777281078 22
1777281083 22
```
</details>

---

