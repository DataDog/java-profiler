---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 13:49:35 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 69-74 cores)</summary>

```
1793295822 74
1793295827 74
1793295832 74
1793295837 74
1793295842 74
1793295847 74
1793295852 74
1793295857 74
1793295862 69
1793295867 69
1793295872 69
1793295877 69
1793295882 69
1793295887 69
1793295892 69
1793295897 69
1793295902 69
1793295907 69
1793295912 69
1793295917 69
```
</details>

---

