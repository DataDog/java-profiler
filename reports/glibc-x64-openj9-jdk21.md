---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 06:28:25 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1795087388 85
1795087393 85
1795087398 94
1795087403 94
1795087408 94
1795087413 94
1795087418 94
1795087423 94
1795087428 94
1795087433 94
1795087438 94
1795087443 94
1795087448 94
1795087453 94
1795087458 94
1795087463 94
1795087468 94
1795087473 94
1795087478 96
1795087483 96
```
</details>

---

