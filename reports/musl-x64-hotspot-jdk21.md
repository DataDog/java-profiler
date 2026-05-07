---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 07:09:48 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 64 |
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
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (5 unique values: 62-72 cores)</summary>

```
1778151761 72
1778151766 62
1778151771 62
1778151776 62
1778151781 62
1778151786 67
1778151791 67
1778151796 69
1778151801 69
1778151806 69
1778151811 69
1778151816 69
1778151821 69
1778151826 69
1778151831 69
1778151836 69
1778151841 69
1778151846 69
1778151851 69
1778151856 69
```
</details>

---

