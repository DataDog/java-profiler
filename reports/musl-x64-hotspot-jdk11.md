---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 15:54:55 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 87-94 cores)</summary>

```
1777405573 92
1777405578 92
1777405583 92
1777405588 92
1777405593 92
1777405598 92
1777405603 92
1777405608 92
1777405613 92
1777405618 92
1777405623 92
1777405628 92
1777405633 92
1777405638 94
1777405643 94
1777405648 91
1777405653 91
1777405658 91
1777405663 87
1777405668 87
```
</details>

---

