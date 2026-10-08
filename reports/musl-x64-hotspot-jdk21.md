---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:54:35 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (6 unique values: 73-89 cores)</summary>

```
1791470920 89
1791470925 89
1791470930 89
1791470935 87
1791470940 87
1791470945 87
1791470950 79
1791470955 79
1791470960 75
1791470965 75
1791470970 75
1791470975 73
1791470980 73
1791470985 73
1791470990 73
1791470995 73
1791471000 73
1791471005 75
1791471010 75
1791471015 75
```
</details>

---

