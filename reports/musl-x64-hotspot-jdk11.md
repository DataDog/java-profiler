---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 07:51:10 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (5 unique values: 60-77 cores)</summary>

```
1795610860 75
1795610865 75
1795610870 77
1795610875 77
1795610880 71
1795610885 71
1795610890 71
1795610895 71
1795610900 71
1795610905 71
1795610910 62
1795610915 62
1795610920 60
1795610925 60
1795610930 60
1795610935 60
1795610940 60
1795610945 60
1795610950 60
1795610955 60
```
</details>

---

