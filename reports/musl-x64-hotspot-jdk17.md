---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-27 21:22:40 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 58-96 cores)</summary>

```
1790558258 58
1790558263 58
1790558268 58
1790558273 58
1790558278 58
1790558283 58
1790558288 58
1790558293 96
1790558298 96
1790558303 96
1790558308 96
1790558313 96
1790558318 96
1790558323 96
1790558328 96
1790558333 96
1790558338 96
1790558343 96
1790558348 96
1790558353 96
```
</details>

---

