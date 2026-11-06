---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 10:29:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 8 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 24-26 cores)</summary>

```
1793978562 24
1793978567 24
1793978572 24
1793978577 24
1793978582 24
1793978588 24
1793978593 24
1793978598 24
1793978603 24
1793978608 24
1793978613 24
1793978618 24
1793978623 24
1793978628 24
1793978633 24
1793978638 24
1793978643 24
1793978648 26
1793978653 26
1793978658 26
```
</details>

---

