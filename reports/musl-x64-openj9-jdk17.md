---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:01:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 89-94 cores)</summary>

```
1795431354 92
1795431359 94
1795431364 94
1795431369 94
1795431374 94
1795431379 94
1795431384 94
1795431389 94
1795431394 94
1795431399 94
1795431404 89
1795431409 89
1795431414 89
1795431419 91
1795431425 91
1795431430 91
1795431435 91
1795431440 91
1795431445 91
1795431450 91
```
</details>

---

