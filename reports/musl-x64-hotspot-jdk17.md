---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-12 10:27:01 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 12 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (7 unique values: 53-61 cores)</summary>

```
1773325272 61
1773325277 61
1773325282 56
1773325287 56
1773325292 56
1773325297 56
1773325302 57
1773325307 57
1773325312 57
1773325317 53
1773325322 53
1773325327 55
1773325332 55
1773325337 55
1773325342 55
1773325347 58
1773325352 58
1773325357 58
1773325362 59
1773325367 59
```
</details>

---

