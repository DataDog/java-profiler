---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:18:31 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 64-96 cores)</summary>

```
1786972358 96
1786972363 96
1786972368 96
1786972373 64
1786972378 64
1786972383 64
1786972388 64
1786972393 64
1786972398 64
1786972403 64
1786972408 64
1786972413 64
1786972418 64
1786972423 64
1786972428 64
1786972433 64
1786972438 64
1786972443 64
1786972448 64
1786972453 64
```
</details>

---

