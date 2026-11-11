---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 05:46:26 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1794393747 53
1794393752 53
1794393757 53
1794393762 53
1794393767 53
1794393772 53
1794393777 53
1794393782 53
1794393787 53
1794393792 53
1794393797 53
1794393802 53
1794393807 53
1794393812 53
1794393817 53
1794393822 53
1794393827 53
1794393832 53
1794393837 55
1794393842 55
```
</details>

---

