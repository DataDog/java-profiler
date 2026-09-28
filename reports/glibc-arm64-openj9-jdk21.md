---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-27 21:22:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 10 |
| Allocations | 206 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1790558297 13
1790558302 13
1790558307 13
1790558312 18
1790558317 18
1790558322 18
1790558327 18
1790558332 18
1790558337 18
1790558342 18
1790558347 18
1790558352 18
1790558357 18
1790558362 18
1790558367 18
1790558372 18
1790558377 18
1790558382 18
1790558387 18
1790558392 18
```
</details>

---

