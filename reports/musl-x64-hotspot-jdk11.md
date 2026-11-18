---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:20:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 49-62 cores)</summary>

```
1795014923 62
1795014928 62
1795014933 62
1795014938 62
1795014943 62
1795014948 62
1795014953 62
1795014958 62
1795014963 62
1795014968 49
1795014973 49
1795014978 49
1795014983 49
1795014988 49
1795014993 49
1795014998 49
1795015003 49
1795015008 49
1795015013 49
1795015018 49
```
</details>

---

