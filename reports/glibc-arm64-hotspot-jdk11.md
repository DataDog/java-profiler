---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:26:02 EST

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
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 8 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1050 |
| Sample Rate | 17.50/sec |
| Health Score | 1094% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794489697 51
1794489702 51
1794489707 51
1794489712 51
1794489717 51
1794489722 51
1794489727 51
1794489732 51
1794489737 51
1794489742 51
1794489747 51
1794489752 51
1794489757 51
1794489762 64
1794489767 64
1794489772 64
1794489777 64
1794489782 64
1794489787 64
1794489792 64
```
</details>

---

