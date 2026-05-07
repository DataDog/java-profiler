---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-07 06:49:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 80-91 cores)</summary>

```
1778150761 91
1778150766 89
1778150771 89
1778150776 91
1778150781 91
1778150786 91
1778150791 91
1778150796 91
1778150801 91
1778150806 91
1778150811 91
1778150816 91
1778150821 87
1778150826 87
1778150831 87
1778150836 87
1778150841 83
1778150846 83
1778150851 83
1778150856 83
```
</details>

---

