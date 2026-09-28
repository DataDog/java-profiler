---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 10:16:36 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 47-50 cores)</summary>

```
1790604693 49
1790604698 49
1790604703 49
1790604708 49
1790604713 49
1790604718 47
1790604724 47
1790604729 49
1790604734 49
1790604739 49
1790604744 49
1790604749 48
1790604754 48
1790604759 50
1790604764 50
1790604769 50
1790604774 50
1790604779 50
1790604784 50
1790604789 50
```
</details>

---

