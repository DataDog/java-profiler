---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 10:11:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 55-60 cores)</summary>

```
1777471553 60
1777471559 60
1777471564 60
1777471569 60
1777471574 60
1777471579 60
1777471584 60
1777471589 60
1777471594 60
1777471599 60
1777471604 55
1777471609 55
1777471614 55
1777471619 55
1777471624 55
1777471629 55
1777471634 55
1777471639 55
1777471644 55
1777471649 55
```
</details>

---

