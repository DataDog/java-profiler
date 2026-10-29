---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 07:57:21 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 888 |
| Sample Rate | 14.80/sec |
| Health Score | 925% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 64-67 cores)</summary>

```
1793274795 67
1793274800 67
1793274805 67
1793274810 67
1793274815 67
1793274820 67
1793274825 67
1793274830 67
1793274835 67
1793274840 67
1793274845 67
1793274850 67
1793274855 67
1793274860 67
1793274865 67
1793274870 67
1793274875 64
1793274880 64
1793274885 64
1793274890 64
```
</details>

---

