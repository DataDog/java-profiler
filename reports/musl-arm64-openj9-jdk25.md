---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:06:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1795449558 28
1795449563 28
1795449568 28
1795449573 28
1795449578 23
1795449583 23
1795449588 23
1795449593 23
1795449598 23
1795449603 23
1795449608 28
1795449613 28
1795449618 28
1795449623 28
1795449628 28
1795449633 28
1795449638 28
1795449643 28
1795449648 28
1795449653 28
```
</details>

---

