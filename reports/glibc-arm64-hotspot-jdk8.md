---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-17 16:48:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 14-48 cores)</summary>

```
1789677761 48
1789677766 48
1789677771 48
1789677776 48
1789677781 48
1789677786 48
1789677791 48
1789677796 14
1789677801 14
1789677806 14
1789677811 14
1789677816 14
1789677821 14
1789677826 14
1789677831 14
1789677836 14
1789677841 14
1789677846 14
1789677851 14
1789677856 14
```
</details>

---

