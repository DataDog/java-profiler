---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-15 08:56:21 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794750682 81
1794750687 81
1794750692 79
1794750697 79
1794750702 79
1794750707 79
1794750712 81
1794750717 81
1794750722 81
1794750727 81
1794750732 81
1794750737 81
1794750742 81
1794750747 81
1794750752 81
1794750757 81
1794750762 81
1794750767 81
1794750772 81
1794750777 81
```
</details>

---

