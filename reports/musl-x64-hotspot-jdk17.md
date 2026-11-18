---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:20:06 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 66-83 cores)</summary>

```
1795014958 68
1795014963 68
1795014968 68
1795014973 68
1795014978 66
1795014983 66
1795014988 66
1795014993 66
1795014998 66
1795015003 66
1795015008 66
1795015013 66
1795015018 66
1795015023 66
1795015028 66
1795015033 66
1795015038 66
1795015043 66
1795015048 66
1795015053 83
```
</details>

---

