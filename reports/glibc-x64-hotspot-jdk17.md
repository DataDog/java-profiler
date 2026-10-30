---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 11:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 38-41 cores)</summary>

```
1793374859 39
1793374864 39
1793374869 39
1793374874 39
1793374879 39
1793374884 39
1793374889 39
1793374894 39
1793374899 39
1793374904 39
1793374909 39
1793374914 39
1793374919 39
1793374924 41
1793374929 41
1793374934 38
1793374939 38
1793374944 38
1793374949 38
1793374954 38
```
</details>

---

