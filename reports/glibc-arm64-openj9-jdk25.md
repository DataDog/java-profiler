---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 07:06:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 14 |
| Allocations | 166 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1790074889 49
1790074894 64
1790074899 64
1790074904 64
1790074909 64
1790074914 64
1790074919 64
1790074924 64
1790074929 64
1790074934 64
1790074939 64
1790074944 64
1790074949 64
1790074954 64
1790074959 64
1790074964 64
1790074969 64
1790074974 64
1790074979 64
1790074984 64
```
</details>

---

