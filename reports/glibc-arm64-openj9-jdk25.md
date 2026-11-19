---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 09:29:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 29-31 cores)</summary>

```
1795098321 29
1795098326 29
1795098331 29
1795098336 29
1795098341 29
1795098346 29
1795098351 29
1795098357 29
1795098362 29
1795098367 29
1795098372 29
1795098377 29
1795098382 29
1795098387 29
1795098392 29
1795098397 29
1795098402 29
1795098407 29
1795098412 29
1795098417 29
```
</details>

---

