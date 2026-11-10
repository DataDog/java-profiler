---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 18:15:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (4 unique values: 50-59 cores)</summary>

```
1794352252 59
1794352257 59
1794352262 59
1794352267 58
1794352272 58
1794352277 58
1794352283 58
1794352288 58
1794352293 58
1794352298 58
1794352303 58
1794352308 50
1794352313 50
1794352318 50
1794352323 50
1794352328 51
1794352333 51
1794352338 51
1794352343 51
1794352348 51
```
</details>

---

