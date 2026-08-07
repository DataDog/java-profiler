---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-07 12:24:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 8 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 7-9 cores)</summary>

```
1786119558 9
1786119563 9
1786119568 9
1786119573 9
1786119578 9
1786119583 9
1786119588 9
1786119593 9
1786119598 9
1786119603 9
1786119608 9
1786119613 9
1786119618 7
1786119623 7
1786119628 7
1786119633 7
1786119638 7
1786119643 7
1786119648 7
1786119653 7
```
</details>

---

