---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 18:14:39 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 32-38 cores)</summary>

```
1794352239 38
1794352244 38
1794352249 38
1794352254 38
1794352260 38
1794352265 33
1794352270 33
1794352275 33
1794352280 33
1794352285 33
1794352290 33
1794352295 33
1794352300 33
1794352305 33
1794352310 33
1794352315 33
1794352320 33
1794352325 33
1794352330 33
1794352335 33
```
</details>

---

