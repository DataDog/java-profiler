---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 10:59:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793721306 46
1793721311 46
1793721316 51
1793721321 51
1793721326 51
1793721331 51
1793721336 51
1793721341 51
1793721346 51
1793721351 51
1793721356 51
1793721361 51
1793721366 51
1793721371 51
1793721376 51
1793721381 51
1793721386 51
1793721391 51
1793721396 51
1793721401 51
```
</details>

---

