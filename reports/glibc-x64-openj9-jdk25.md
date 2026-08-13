---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-13 04:53:02 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 39-41 cores)</summary>

```
1786610888 39
1786610893 39
1786610898 39
1786610903 39
1786610908 39
1786610913 39
1786610918 39
1786610923 39
1786610928 39
1786610933 39
1786610938 41
1786610943 41
1786610948 41
1786610953 41
1786610958 41
1786610963 41
1786610968 41
1786610973 41
1786610978 41
1786610983 41
```
</details>

---

