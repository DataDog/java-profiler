---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 12:21:45 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 79-94 cores)</summary>

```
1794331000 90
1794331005 90
1794331010 90
1794331015 90
1794331020 90
1794331025 90
1794331030 90
1794331035 90
1794331040 90
1794331045 94
1794331050 94
1794331055 79
1794331060 79
1794331065 79
1794331070 79
1794331075 79
1794331081 79
1794331086 79
1794331091 79
1794331096 79
```
</details>

---

