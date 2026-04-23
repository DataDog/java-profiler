---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-23 12:53:32 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 39-48 cores)</summary>

```
1776962898 48
1776962903 48
1776962908 48
1776962913 39
1776962918 39
1776962923 39
1776962928 39
1776962933 39
1776962938 39
1776962943 39
1776962948 39
1776962953 39
1776962958 39
1776962963 39
1776962968 39
1776962973 39
1776962978 39
1776962983 39
1776962988 39
1776962993 39
```
</details>

---

