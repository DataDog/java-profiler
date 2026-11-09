---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-09 05:57:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 50-56 cores)</summary>

```
1794221553 50
1794221558 50
1794221563 50
1794221568 50
1794221573 50
1794221578 54
1794221583 54
1794221588 54
1794221593 54
1794221598 54
1794221603 54
1794221608 54
1794221613 54
1794221618 54
1794221623 54
1794221628 54
1794221633 54
1794221638 54
1794221643 54
1794221648 54
```
</details>

---

