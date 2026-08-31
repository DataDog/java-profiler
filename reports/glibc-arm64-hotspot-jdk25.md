---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-30 21:21:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 15 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (3 unique values: 30-40 cores)</summary>

```
1788138983 30
1788138988 30
1788138993 30
1788138998 30
1788139003 30
1788139008 30
1788139013 30
1788139018 30
1788139023 30
1788139028 30
1788139033 35
1788139038 35
1788139043 40
1788139048 40
1788139053 40
1788139058 40
1788139063 40
1788139068 40
1788139073 40
1788139078 40
```
</details>

---

