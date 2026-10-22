---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 12:39:25 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 50-67 cores)</summary>

```
1792686819 67
1792686824 67
1792686829 67
1792686834 67
1792686839 67
1792686844 50
1792686849 50
1792686854 50
1792686859 50
1792686864 50
1792686869 50
1792686874 50
1792686879 50
1792686884 50
1792686889 50
1792686894 50
1792686899 50
1792686904 50
1792686909 50
1792686914 50
```
</details>

---

