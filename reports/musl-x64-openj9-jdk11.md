---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 20:15:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 30-34 cores)</summary>

```
1787357478 30
1787357483 30
1787357488 30
1787357493 32
1787357498 32
1787357503 32
1787357508 32
1787357513 32
1787357518 32
1787357523 32
1787357529 32
1787357534 32
1787357539 32
1787357544 32
1787357549 32
1787357554 32
1787357559 32
1787357564 32
1787357569 32
1787357574 34
```
</details>

---

