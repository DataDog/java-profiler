---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 09:56:09 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 9 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793890280 48
1793890285 48
1793890290 48
1793890295 48
1793890300 46
1793890305 46
1793890310 46
1793890315 46
1793890320 46
1793890325 46
1793890330 46
1793890335 46
1793890340 46
1793890345 46
1793890351 46
1793890356 46
1793890361 46
1793890366 46
1793890371 46
1793890376 46
```
</details>

---

