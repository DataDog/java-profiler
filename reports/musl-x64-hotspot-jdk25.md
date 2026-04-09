---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-09 05:05:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (7 unique values: 69-89 cores)</summary>

```
1775725271 84
1775725276 84
1775725281 84
1775725286 84
1775725291 89
1775725296 89
1775725301 89
1775725306 89
1775725311 89
1775725316 89
1775725321 87
1775725326 87
1775725331 87
1775725336 81
1775725341 81
1775725346 81
1775725351 81
1775725356 71
1775725361 71
1775725366 71
```
</details>

---

