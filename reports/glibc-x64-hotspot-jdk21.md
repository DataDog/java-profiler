---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 05:16:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 73-78 cores)</summary>

```
1792141895 73
1792141900 75
1792141905 75
1792141910 75
1792141915 75
1792141920 75
1792141925 75
1792141930 75
1792141935 75
1792141940 75
1792141945 78
1792141950 78
1792141955 78
1792141960 78
1792141965 78
1792141970 78
1792141975 78
1792141980 78
1792141985 76
1792141990 76
```
</details>

---

