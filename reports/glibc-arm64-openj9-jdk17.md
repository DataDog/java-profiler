---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 08:42:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 370 |
| Sample Rate | 6.17/sec |
| Health Score | 386% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 39-46 cores)</summary>

```
1794836328 43
1794836333 43
1794836338 43
1794836343 43
1794836348 43
1794836353 41
1794836358 41
1794836363 41
1794836368 41
1794836373 41
1794836378 41
1794836383 41
1794836388 41
1794836393 41
1794836398 41
1794836403 41
1794836408 41
1794836413 39
1794836418 39
1794836423 39
```
</details>

---

