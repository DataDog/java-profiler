---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:27:48 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 76-81 cores)</summary>

```
1789737683 76
1789737688 76
1789737693 76
1789737698 76
1789737703 76
1789737708 76
1789737713 76
1789737718 76
1789737723 76
1789737728 81
1789737733 81
1789737738 81
1789737743 81
1789737748 81
1789737753 81
1789737758 81
1789737763 81
1789737768 81
1789737773 81
1789737778 81
```
</details>

---

