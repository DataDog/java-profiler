---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 07:16:43 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 64-76 cores)</summary>

```
1786446619 64
1786446624 64
1786446629 64
1786446634 64
1786446639 64
1786446644 64
1786446649 76
1786446654 76
1786446659 76
1786446664 76
1786446669 76
1786446674 76
1786446679 76
1786446684 76
1786446689 76
1786446694 76
1786446699 76
1786446704 76
1786446709 76
1786446714 76
```
</details>

---

