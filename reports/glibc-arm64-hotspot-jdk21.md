---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 13:23:55 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 10 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794334708 48
1794334713 48
1794334718 48
1794334723 48
1794334728 48
1794334733 48
1794334738 48
1794334743 48
1794334748 48
1794334753 48
1794334758 48
1794334763 48
1794334768 47
1794334773 47
1794334778 47
1794334783 47
1794334788 47
1794334793 47
1794334798 47
1794334803 47
```
</details>

---

