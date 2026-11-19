---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 18:13:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 8 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1795129678 14
1795129683 14
1795129688 14
1795129693 14
1795129698 14
1795129703 14
1795129708 14
1795129713 14
1795129718 14
1795129723 14
1795129728 14
1795129733 14
1795129738 14
1795129743 34
1795129748 34
1795129753 34
1795129758 34
1795129763 34
1795129768 34
1795129773 34
```
</details>

---

