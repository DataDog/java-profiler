---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 00:58:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 956 |
| Sample Rate | 15.93/sec |
| Health Score | 996% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1791262471 79
1791262476 79
1791262481 79
1791262486 79
1791262491 81
1791262496 81
1791262501 81
1791262506 81
1791262511 81
1791262516 81
1791262521 81
1791262526 81
1791262531 81
1791262536 81
1791262541 81
1791262546 81
1791262551 79
1791262556 79
1791262561 79
1791262566 79
```
</details>

---

