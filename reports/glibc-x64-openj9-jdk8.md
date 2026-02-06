---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-06 09:39:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1770388390 32
1770388395 32
1770388400 32
1770388405 32
1770388410 32
1770388415 32
1770388420 32
1770388425 32
1770388430 32
1770388435 32
1770388440 32
1770388445 32
1770388450 32
1770388455 32
1770388460 32
1770388465 32
1770388470 32
1770388475 32
1770388480 32
1770388485 29
```
</details>

---

