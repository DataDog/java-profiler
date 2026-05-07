---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 13:17:02 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 14 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778173861 64
1778173866 64
1778173871 64
1778173876 64
1778173881 64
1778173886 64
1778173891 64
1778173896 64
1778173901 64
1778173906 64
1778173911 64
1778173916 64
1778173921 64
1778173926 64
1778173931 64
1778173936 64
1778173941 64
1778173946 64
1778173951 59
1778173956 59
```
</details>

---

