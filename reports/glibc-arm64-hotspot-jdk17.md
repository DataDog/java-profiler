---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-16 12:13:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 12 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789574839 48
1789574844 48
1789574849 48
1789574854 48
1789574860 48
1789574865 48
1789574870 48
1789574875 48
1789574880 48
1789574885 48
1789574890 48
1789574895 48
1789574900 48
1789574905 48
1789574910 48
1789574915 48
1789574920 48
1789574925 43
1789574930 43
1789574935 43
```
</details>

---

