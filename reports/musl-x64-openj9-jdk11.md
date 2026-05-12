---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 09:20:30 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 881 |
| Sample Rate | 14.68/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1778591621 96
1778591626 96
1778591631 87
1778591636 87
1778591641 87
1778591646 87
1778591651 87
1778591656 87
1778591661 87
1778591666 87
1778591671 87
1778591676 87
1778591681 87
1778591686 87
1778591691 87
1778591696 87
1778591701 87
1778591706 87
1778591711 87
1778591716 87
```
</details>

---

