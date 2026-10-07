---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-07 07:29:47 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791372323 30
1791372328 30
1791372333 30
1791372338 30
1791372343 30
1791372348 30
1791372353 30
1791372358 30
1791372363 30
1791372368 30
1791372373 30
1791372378 30
1791372383 30
1791372388 30
1791372393 30
1791372398 30
1791372404 30
1791372409 30
1791372414 30
1791372419 32
```
</details>

---

