---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 01:04:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 27-58 cores)</summary>

```
1786337963 29
1786337968 29
1786337973 29
1786337978 29
1786337983 29
1786337988 29
1786337993 29
1786337998 29
1786338003 29
1786338008 29
1786338013 29
1786338018 29
1786338023 29
1786338028 29
1786338033 29
1786338038 29
1786338043 29
1786338048 29
1786338053 27
1786338058 27
```
</details>

---

