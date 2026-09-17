---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 19:11:34 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1789686353 35
1789686358 35
1789686363 35
1789686368 35
1789686373 35
1789686378 35
1789686383 35
1789686388 35
1789686393 35
1789686398 40
1789686403 40
1789686408 40
1789686413 40
1789686418 40
1789686423 40
1789686428 40
1789686433 40
1789686438 40
1789686443 40
1789686448 40
```
</details>

---

