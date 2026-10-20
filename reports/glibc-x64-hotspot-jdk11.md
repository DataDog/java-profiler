---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 17:52:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1009 |
| Sample Rate | 16.82/sec |
| Health Score | 1051% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1792532721 94
1792532726 94
1792532731 94
1792532736 94
1792532741 96
1792532746 96
1792532751 96
1792532756 96
1792532761 96
1792532766 96
1792532771 96
1792532776 96
1792532781 96
1792532786 96
1792532791 96
1792532796 96
1792532801 96
1792532806 96
1792532811 96
1792532816 96
```
</details>

---

