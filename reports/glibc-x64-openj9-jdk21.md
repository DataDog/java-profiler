---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:21:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
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
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 51-72 cores)</summary>

```
1794478543 72
1794478548 72
1794478553 51
1794478558 51
1794478563 51
1794478568 51
1794478573 51
1794478578 51
1794478583 51
1794478588 51
1794478593 51
1794478598 51
1794478603 51
1794478608 72
1794478613 72
1794478618 72
1794478623 72
1794478628 72
1794478633 72
1794478638 72
```
</details>

---

