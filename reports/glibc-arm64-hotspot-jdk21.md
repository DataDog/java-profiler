---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 12:37:04 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 16 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 31-51 cores)</summary>

```
1794936795 46
1794936800 46
1794936805 51
1794936810 51
1794936815 51
1794936820 51
1794936825 51
1794936830 51
1794936835 51
1794936840 51
1794936845 51
1794936850 51
1794936855 51
1794936860 51
1794936865 51
1794936870 51
1794936875 51
1794936880 51
1794936885 31
1794936890 31
```
</details>

---

