---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 16:32:54 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 23-33 cores)</summary>

```
1795382915 33
1795382920 33
1795382925 33
1795382930 33
1795382935 33
1795382940 33
1795382945 33
1795382950 33
1795382955 33
1795382960 33
1795382965 33
1795382970 33
1795382975 33
1795382980 33
1795382985 28
1795382990 28
1795382996 28
1795383001 28
1795383006 23
1795383011 23
```
</details>

---

