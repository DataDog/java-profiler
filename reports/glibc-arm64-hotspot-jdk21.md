---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:57:36 EDT

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 11 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (2 unique values: 8-28 cores)</summary>

```
1789677765 8
1789677770 8
1789677775 8
1789677780 8
1789677785 28
1789677790 28
1789677795 28
1789677800 28
1789677805 28
1789677810 28
1789677815 28
1789677820 28
1789677825 28
1789677830 28
1789677835 28
1789677840 28
1789677845 28
1789677850 28
1789677855 28
1789677860 28
```
</details>

---

