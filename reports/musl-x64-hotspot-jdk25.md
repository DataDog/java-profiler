---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:23:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 23-29 cores)</summary>

```
1790853553 29
1790853558 29
1790853563 29
1790853568 29
1790853573 29
1790853578 29
1790853583 29
1790853588 29
1790853593 29
1790853598 28
1790853603 28
1790853608 23
1790853613 23
1790853618 23
1790853623 23
1790853628 23
1790853633 23
1790853638 23
1790853643 23
1790853648 23
```
</details>

---

