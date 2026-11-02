---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 10:00:25 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 13 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793631315 51
1793631320 51
1793631325 51
1793631330 51
1793631335 51
1793631340 51
1793631345 51
1793631350 51
1793631355 51
1793631360 51
1793631365 51
1793631370 51
1793631375 51
1793631380 51
1793631385 51
1793631390 51
1793631395 51
1793631400 51
1793631405 51
1793631410 51
```
</details>

---

