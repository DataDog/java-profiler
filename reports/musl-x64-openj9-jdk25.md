---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 06:31:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 11-41 cores)</summary>

```
1790850356 11
1790850361 11
1790850366 11
1790850371 11
1790850376 11
1790850381 11
1790850386 11
1790850391 11
1790850396 11
1790850402 11
1790850407 11
1790850412 11
1790850417 11
1790850422 11
1790850427 11
1790850432 24
1790850437 24
1790850442 24
1790850447 24
1790850452 24
```
</details>

---

