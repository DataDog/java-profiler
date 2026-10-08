---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:10:21 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1791468223 29
1791468228 29
1791468233 29
1791468238 29
1791468243 29
1791468248 29
1791468253 29
1791468258 29
1791468263 29
1791468268 29
1791468273 29
1791468278 29
1791468283 29
1791468288 27
1791468293 27
1791468298 27
1791468303 19
1791468308 19
1791468313 19
1791468318 19
```
</details>

---

