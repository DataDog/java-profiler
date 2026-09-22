---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 16:59:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (5 unique values: 54-88 cores)</summary>

```
1790110406 54
1790110411 64
1790110416 64
1790110421 64
1790110426 64
1790110431 64
1790110436 64
1790110441 88
1790110446 88
1790110451 88
1790110456 88
1790110461 88
1790110466 88
1790110471 68
1790110476 68
1790110481 68
1790110486 68
1790110491 68
1790110496 68
1790110501 68
```
</details>

---

