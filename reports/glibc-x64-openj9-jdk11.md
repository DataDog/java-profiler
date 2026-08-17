---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 10:37:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 61-73 cores)</summary>

```
1786977221 73
1786977226 73
1786977231 73
1786977236 61
1786977241 61
1786977246 61
1786977251 61
1786977256 61
1786977261 61
1786977266 61
1786977271 61
1786977276 61
1786977281 61
1786977286 61
1786977291 61
1786977296 61
1786977301 61
1786977306 61
1786977311 61
1786977316 61
```
</details>

---

