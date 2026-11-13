---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 08:55:20 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1794577851 80
1794577856 80
1794577861 80
1794577866 80
1794577871 80
1794577876 80
1794577881 80
1794577886 80
1794577891 80
1794577896 80
1794577901 80
1794577906 80
1794577911 80
1794577916 80
1794577921 80
1794577926 80
1794577931 82
1794577936 82
1794577941 82
1794577946 82
```
</details>

---

