---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 08:18:04 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770119066 32
1770119071 32
1770119076 32
1770119081 32
1770119086 32
1770119091 32
1770119096 32
1770119101 32
1770119106 32
1770119111 32
1770119116 32
1770119121 32
1770119126 32
1770119131 32
1770119136 32
1770119141 27
1770119146 27
1770119151 27
1770119156 27
1770119161 27
```
</details>

---

