---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 10:54:19 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 74-81 cores)</summary>

```
1778165412 81
1778165417 81
1778165422 81
1778165427 81
1778165432 79
1778165437 79
1778165442 74
1778165447 74
1778165452 74
1778165457 74
1778165462 74
1778165467 74
1778165472 74
1778165477 74
1778165482 74
1778165487 74
1778165492 74
1778165497 74
1778165502 74
1778165507 74
```
</details>

---

