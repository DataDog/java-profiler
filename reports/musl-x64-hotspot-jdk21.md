---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 09:55:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 66-77 cores)</summary>

```
1793281805 75
1793281810 75
1793281815 75
1793281820 75
1793281825 75
1793281830 75
1793281835 75
1793281840 77
1793281845 77
1793281850 77
1793281855 77
1793281860 77
1793281865 77
1793281870 77
1793281875 77
1793281880 77
1793281885 77
1793281890 77
1793281895 77
1793281900 68
```
</details>

---

