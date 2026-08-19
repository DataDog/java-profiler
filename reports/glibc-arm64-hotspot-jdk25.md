---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 05:17:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 11 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787130864 46
1787130869 46
1787130874 46
1787130879 46
1787130884 46
1787130889 46
1787130894 46
1787130899 46
1787130904 46
1787130909 46
1787130914 46
1787130919 46
1787130924 46
1787130929 46
1787130934 46
1787130939 46
1787130944 46
1787130949 46
1787130954 48
1787130959 48
```
</details>

---

