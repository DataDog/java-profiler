---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 05:49:19 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 74-86 cores)</summary>

```
1786441468 74
1786441473 76
1786441478 76
1786441483 76
1786441488 76
1786441493 76
1786441498 76
1786441503 76
1786441508 76
1786441513 74
1786441518 74
1786441523 74
1786441528 74
1786441533 86
1786441538 86
1786441543 86
1786441548 86
1786441553 86
1786441558 86
1786441563 86
```
</details>

---

