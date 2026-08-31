---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-30 21:21:11 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 942 |
| Sample Rate | 15.70/sec |
| Health Score | 981% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1788138983 76
1788138988 76
1788138993 76
1788138998 76
1788139003 76
1788139008 76
1788139013 76
1788139018 76
1788139023 76
1788139028 96
1788139033 96
1788139038 94
1788139043 94
1788139048 94
1788139053 94
1788139058 94
1788139063 94
1788139068 94
1788139073 96
1788139078 96
```
</details>

---

