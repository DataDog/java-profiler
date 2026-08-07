---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-07 12:24:01 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 10 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 89-94 cores)</summary>

```
1786119558 89
1786119563 89
1786119568 89
1786119573 89
1786119578 89
1786119583 89
1786119588 89
1786119593 91
1786119598 91
1786119603 91
1786119608 91
1786119613 91
1786119618 91
1786119623 94
1786119628 94
1786119633 94
1786119638 94
1786119643 94
1786119648 94
1786119653 94
```
</details>

---

