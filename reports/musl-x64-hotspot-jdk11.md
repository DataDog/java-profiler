---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 08:55:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1794577831 86
1794577836 86
1794577841 86
1794577846 86
1794577851 86
1794577856 84
1794577861 84
1794577866 84
1794577871 84
1794577876 84
1794577881 84
1794577886 84
1794577891 84
1794577896 84
1794577901 84
1794577906 84
1794577911 84
1794577916 84
1794577921 84
1794577926 84
```
</details>

---

