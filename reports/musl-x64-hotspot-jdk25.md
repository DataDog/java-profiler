---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:20:52 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1795641348 53
1795641353 53
1795641358 53
1795641363 53
1795641368 53
1795641373 53
1795641378 53
1795641383 53
1795641388 53
1795641393 53
1795641398 53
1795641403 53
1795641408 53
1795641413 55
1795641418 55
1795641423 55
1795641428 55
1795641433 55
1795641438 55
1795641443 55
```
</details>

---

