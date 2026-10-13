---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-13 07:44:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1791891529 40
1791891534 40
1791891539 40
1791891544 40
1791891549 40
1791891554 40
1791891559 40
1791891564 40
1791891569 40
1791891574 40
1791891579 40
1791891584 42
1791891589 42
1791891594 42
1791891599 42
1791891604 42
1791891609 42
1791891614 42
1791891619 42
1791891624 42
```
</details>

---

