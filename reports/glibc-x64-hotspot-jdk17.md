---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 12:23:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 70-73 cores)</summary>

```
1786119648 70
1786119653 73
1786119658 73
1786119663 73
1786119668 73
1786119673 73
1786119678 73
1786119683 71
1786119688 71
1786119693 70
1786119698 70
1786119703 70
1786119708 70
1786119713 70
1786119718 70
1786119723 70
1786119728 70
1786119733 70
1786119738 70
1786119743 70
```
</details>

---

