---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 08:33:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1793017778 82
1793017783 82
1793017788 82
1793017793 84
1793017798 84
1793017803 84
1793017808 84
1793017813 84
1793017818 84
1793017823 84
1793017828 84
1793017833 86
1793017839 86
1793017844 86
1793017849 86
1793017854 86
1793017859 86
1793017864 86
1793017869 86
1793017874 86
```
</details>

---

