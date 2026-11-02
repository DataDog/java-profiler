---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 17:11:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 20-30 cores)</summary>

```
1793656935 20
1793656940 20
1793656945 20
1793656950 20
1793656955 20
1793656960 30
1793656965 30
1793656970 30
1793656975 30
1793656980 29
1793656985 29
1793656990 29
1793656995 29
1793657000 29
1793657005 29
1793657010 29
1793657015 29
1793657020 29
1793657025 29
1793657030 29
```
</details>

---

