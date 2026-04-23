---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 12:53:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 39-48 cores)</summary>

```
1776962876 48
1776962881 48
1776962886 48
1776962891 48
1776962896 48
1776962901 48
1776962906 48
1776962911 39
1776962916 39
1776962921 39
1776962926 39
1776962931 39
1776962936 39
1776962941 39
1776962946 39
1776962951 39
1776962956 39
1776962961 39
1776962966 39
1776962971 39
```
</details>

---

