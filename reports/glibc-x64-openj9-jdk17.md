---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:27:49 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 86-96 cores)</summary>

```
1789737668 86
1789737673 86
1789737678 86
1789737683 86
1789737688 86
1789737693 86
1789737698 86
1789737703 86
1789737708 86
1789737713 86
1789737718 86
1789737723 96
1789737728 96
1789737733 96
1789737738 96
1789737743 96
1789737748 96
1789737753 96
1789737758 96
1789737763 96
```
</details>

---

