---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-24 08:31:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 49-54 cores)</summary>

```
1777033613 53
1777033618 53
1777033623 53
1777033628 53
1777033633 53
1777033638 53
1777033643 52
1777033648 52
1777033653 54
1777033658 54
1777033663 54
1777033668 54
1777033673 54
1777033678 54
1777033683 54
1777033688 54
1777033693 54
1777033698 54
1777033703 49
1777033708 49
```
</details>

---

