---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-15 08:56:21 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794750710 79
1794750715 79
1794750721 81
1794750726 81
1794750731 81
1794750736 81
1794750741 81
1794750746 81
1794750751 81
1794750756 81
1794750761 81
1794750766 81
1794750771 81
1794750776 81
1794750781 81
1794750786 81
1794750791 81
1794750796 81
1794750801 81
1794750806 81
```
</details>

---

