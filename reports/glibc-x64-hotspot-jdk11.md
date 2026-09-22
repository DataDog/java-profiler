---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 07:06:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 895 |
| Sample Rate | 14.92/sec |
| Health Score | 932% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1790074847 32
1790074852 32
1790074857 32
1790074862 32
1790074867 32
1790074872 32
1790074877 32
1790074882 32
1790074887 32
1790074892 32
1790074897 32
1790074902 32
1790074907 32
1790074912 32
1790074917 32
1790074922 32
1790074927 30
1790074932 30
1790074937 30
1790074942 30
```
</details>

---

