---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:06:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1794430782 90
1794430787 90
1794430792 90
1794430797 90
1794430802 90
1794430807 90
1794430812 90
1794430817 90
1794430822 92
1794430827 92
1794430832 92
1794430837 92
1794430842 92
1794430847 92
1794430852 92
1794430857 92
1794430862 92
1794430867 92
1794430872 92
1794430877 92
```
</details>

---

