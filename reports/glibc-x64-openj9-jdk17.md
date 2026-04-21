---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-21 14:31:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1776795956 28
1776795961 28
1776795966 28
1776795971 28
1776795976 28
1776795981 28
1776795986 28
1776795991 28
1776795996 28
1776796001 28
1776796006 28
1776796011 28
1776796016 28
1776796021 28
1776796026 28
1776796031 32
1776796036 32
1776796041 32
1776796046 32
1776796051 32
```
</details>

---

