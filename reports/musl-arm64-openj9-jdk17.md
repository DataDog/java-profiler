---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-08 09:20:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1791465306 51
1791465311 46
1791465316 46
1791465321 46
1791465326 46
1791465331 46
1791465336 46
1791465341 46
1791465346 46
1791465351 46
1791465356 46
1791465361 46
1791465366 46
1791465371 51
1791465376 51
1791465381 51
1791465386 51
1791465391 51
1791465396 51
1791465401 51
```
</details>

---

