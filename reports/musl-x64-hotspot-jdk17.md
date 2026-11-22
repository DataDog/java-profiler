---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 16:32:55 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 15-43 cores)</summary>

```
1795382890 19
1795382895 19
1795382900 19
1795382905 19
1795382910 19
1795382915 19
1795382920 17
1795382925 17
1795382930 17
1795382935 17
1795382940 17
1795382945 43
1795382950 43
1795382955 15
1795382960 15
1795382965 17
1795382970 17
1795382975 17
1795382980 17
1795382985 26
```
</details>

---

