---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-30 04:28:20 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 20.10/sec |
| Health Score | 1256% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 22.63/sec |
| Health Score | 1414% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1769764973 32
1769764978 32
1769764983 32
1769764988 32
1769764993 32
1769764998 32
1769765003 32
1769765008 32
1769765013 32
1769765018 32
1769765023 32
1769765028 32
1769765033 32
1769765038 32
1769765043 32
1769765048 32
1769765053 32
1769765058 32
1769765063 32
1769765068 32
```
</details>

---

