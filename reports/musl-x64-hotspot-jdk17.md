---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-06 04:35:14 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 16-24 cores)</summary>

```
1772789312 22
1772789317 22
1772789322 24
1772789327 24
1772789332 19
1772789337 19
1772789342 19
1772789347 19
1772789352 16
1772789357 16
1772789362 16
1772789368 16
1772789373 16
1772789378 16
1772789383 16
1772789388 16
1772789393 21
1772789398 21
1772789403 21
1772789408 21
```
</details>

---

