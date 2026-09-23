---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 09:09:11 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 8 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 42-50 cores)</summary>

```
1790168760 42
1790168765 42
1790168770 42
1790168775 42
1790168780 42
1790168785 42
1790168790 42
1790168795 42
1790168800 42
1790168805 42
1790168810 42
1790168815 42
1790168820 42
1790168825 42
1790168830 42
1790168835 42
1790168840 42
1790168845 42
1790168850 42
1790168855 42
```
</details>

---

