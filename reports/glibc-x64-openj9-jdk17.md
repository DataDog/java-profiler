---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-27 21:22:39 EDT

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 8-32 cores)</summary>

```
1790558267 8
1790558272 8
1790558277 8
1790558282 8
1790558287 8
1790558292 8
1790558297 8
1790558302 8
1790558307 8
1790558312 23
1790558317 23
1790558322 23
1790558327 23
1790558332 23
1790558337 23
1790558342 23
1790558347 23
1790558352 32
1790558357 32
1790558362 32
```
</details>

---

