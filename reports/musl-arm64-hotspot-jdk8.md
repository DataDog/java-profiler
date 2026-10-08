---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-08 10:54:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 33-42 cores)</summary>

```
1791470938 39
1791470943 39
1791470948 39
1791470953 39
1791470958 39
1791470963 39
1791470968 33
1791470973 33
1791470978 38
1791470983 38
1791470988 38
1791470993 38
1791470998 38
1791471003 38
1791471008 38
1791471013 38
1791471018 39
1791471023 39
1791471028 39
1791471033 39
```
</details>

---

