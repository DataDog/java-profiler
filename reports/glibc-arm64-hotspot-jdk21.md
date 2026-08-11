---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 07:16:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1786446594 51
1786446599 51
1786446604 51
1786446609 51
1786446614 51
1786446619 51
1786446624 51
1786446629 51
1786446634 51
1786446639 51
1786446644 51
1786446649 51
1786446654 51
1786446659 51
1786446664 39
1786446669 39
1786446674 39
1786446679 39
1786446684 39
1786446689 39
```
</details>

---

