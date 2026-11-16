---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 05:31:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794824779 32
1794824784 32
1794824789 32
1794824794 32
1794824799 32
1794824804 32
1794824809 32
1794824814 32
1794824819 32
1794824824 32
1794824829 32
1794824835 32
1794824840 32
1794824845 32
1794824850 32
1794824855 32
1794824860 32
1794824865 32
1794824870 32
1794824875 32
```
</details>

---

