---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 22:42:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1788575847 59
1788575852 59
1788575857 59
1788575862 59
1788575867 59
1788575872 59
1788575877 59
1788575882 61
1788575887 61
1788575892 61
1788575897 61
1788575902 61
1788575907 61
1788575912 61
1788575917 61
1788575922 61
1788575927 61
1788575932 61
1788575937 61
1788575942 61
```
</details>

---

