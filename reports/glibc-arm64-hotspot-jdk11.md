---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 12:37:04 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794936765 51
1794936770 51
1794936776 51
1794936781 51
1794936786 51
1794936791 51
1794936796 51
1794936801 51
1794936806 51
1794936811 51
1794936816 51
1794936821 51
1794936826 51
1794936831 51
1794936836 51
1794936841 51
1794936846 64
1794936851 64
1794936856 64
1794936861 64
```
</details>

---

