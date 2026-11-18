---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:33:15 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 919 |
| Sample Rate | 15.32/sec |
| Health Score | 957% |
| Threads | 11 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (3 unique values: 46-50 cores)</summary>

```
1795015598 46
1795015603 46
1795015608 46
1795015613 46
1795015618 46
1795015623 46
1795015628 46
1795015633 46
1795015638 46
1795015643 46
1795015648 46
1795015653 46
1795015658 46
1795015663 48
1795015668 48
1795015673 48
1795015678 48
1795015683 48
1795015689 50
1795015694 50
```
</details>

---

