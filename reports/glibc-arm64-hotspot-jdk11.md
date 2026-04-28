---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 15:54:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 7 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777405573 64
1777405578 64
1777405583 64
1777405588 64
1777405593 64
1777405598 64
1777405603 64
1777405608 64
1777405613 64
1777405618 64
1777405623 64
1777405628 59
1777405633 59
1777405638 59
1777405643 59
1777405648 59
1777405653 59
1777405658 59
1777405663 59
1777405668 59
```
</details>

---

