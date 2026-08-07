---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 12:24:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 43-63 cores)</summary>

```
1786119558 43
1786119563 43
1786119568 43
1786119573 43
1786119578 43
1786119583 43
1786119588 45
1786119593 45
1786119598 45
1786119603 45
1786119608 43
1786119613 43
1786119618 43
1786119623 43
1786119628 43
1786119633 43
1786119638 43
1786119643 43
1786119648 43
1786119653 43
```
</details>

---

