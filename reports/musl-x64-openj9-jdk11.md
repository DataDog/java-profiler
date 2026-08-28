---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-28 08:40:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 71-81 cores)</summary>

```
1787920538 71
1787920543 71
1787920548 71
1787920553 71
1787920558 73
1787920563 73
1787920568 73
1787920573 73
1787920578 73
1787920583 73
1787920588 73
1787920593 73
1787920598 73
1787920604 73
1787920609 73
1787920614 73
1787920619 81
1787920624 81
1787920629 81
1787920634 81
```
</details>

---

