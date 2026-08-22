---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 14:20:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1787422553 56
1787422558 56
1787422563 56
1787422568 54
1787422573 54
1787422578 54
1787422583 54
1787422588 54
1787422593 54
1787422598 54
1787422603 54
1787422608 56
1787422613 56
1787422618 56
1787422623 56
1787422628 56
1787422633 56
1787422638 56
1787422643 56
1787422648 56
```
</details>

---

