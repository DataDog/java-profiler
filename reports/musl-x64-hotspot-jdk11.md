---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 15:36:45 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 975 |
| Sample Rate | 16.25/sec |
| Health Score | 1016% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1794256280 64
1794256285 64
1794256290 64
1794256295 64
1794256300 64
1794256305 64
1794256310 64
1794256315 64
1794256320 66
1794256325 66
1794256330 66
1794256335 66
1794256340 66
1794256345 66
1794256350 66
1794256355 66
1794256360 66
1794256365 66
1794256370 66
1794256375 66
```
</details>

---

