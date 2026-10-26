---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 08:33:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (4 unique values: 55-80 cores)</summary>

```
1793017764 80
1793017769 80
1793017774 80
1793017779 55
1793017784 55
1793017789 55
1793017794 57
1793017799 57
1793017804 57
1793017809 65
1793017814 65
1793017819 65
1793017824 65
1793017829 65
1793017834 65
1793017839 65
1793017844 65
1793017849 65
1793017854 65
1793017859 65
```
</details>

---

