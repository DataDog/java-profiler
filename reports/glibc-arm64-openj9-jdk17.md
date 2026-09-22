---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 05:59:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1790070779 16
1790070784 16
1790070789 16
1790070794 16
1790070799 16
1790070804 16
1790070809 16
1790070814 16
1790070819 16
1790070824 16
1790070829 16
1790070834 16
1790070839 16
1790070844 16
1790070849 16
1790070854 16
1790070859 16
1790070864 16
1790070869 16
1790070874 16
```
</details>

---

