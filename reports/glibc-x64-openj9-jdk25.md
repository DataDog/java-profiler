---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 18:32:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (4 unique values: 47-66 cores)</summary>

```
1778538422 47
1778538427 47
1778538432 47
1778538437 47
1778538442 47
1778538447 47
1778538452 47
1778538457 47
1778538462 47
1778538467 47
1778538472 47
1778538477 47
1778538482 47
1778538487 47
1778538492 47
1778538497 47
1778538502 52
1778538507 52
1778538512 56
1778538517 56
```
</details>

---

