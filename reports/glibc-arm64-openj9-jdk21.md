---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 07:57:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 15 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793274844 30
1793274849 30
1793274854 30
1793274859 30
1793274864 30
1793274869 30
1793274874 30
1793274879 30
1793274884 30
1793274889 30
1793274894 30
1793274899 30
1793274904 30
1793274909 30
1793274914 30
1793274919 30
1793274924 30
1793274929 30
1793274934 30
1793274939 30
```
</details>

---

