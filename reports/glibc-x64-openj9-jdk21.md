---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:20:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (4 unique values: 35-72 cores)</summary>

```
1795641378 72
1795641383 72
1795641388 44
1795641393 44
1795641398 44
1795641403 44
1795641408 44
1795641413 44
1795641418 35
1795641423 35
1795641428 35
1795641433 35
1795641438 35
1795641443 35
1795641448 35
1795641453 44
1795641458 44
1795641463 44
1795641468 44
1795641473 44
```
</details>

---

