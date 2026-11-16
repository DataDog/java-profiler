---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:18:22 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 67-75 cores)</summary>

```
1794823877 71
1794823882 71
1794823887 71
1794823892 71
1794823897 71
1794823902 71
1794823907 71
1794823912 71
1794823917 71
1794823922 71
1794823927 71
1794823932 71
1794823937 67
1794823942 67
1794823947 67
1794823952 67
1794823957 67
1794823962 67
1794823967 67
1794823972 67
```
</details>

---

