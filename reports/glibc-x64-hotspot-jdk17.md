---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 06:10:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1791540268 73
1791540273 73
1791540278 73
1791540283 73
1791540288 71
1791540293 71
1791540298 71
1791540303 71
1791540308 71
1791540313 71
1791540318 71
1791540323 71
1791540328 71
1791540333 71
1791540338 71
1791540343 71
1791540348 71
1791540353 71
1791540358 71
1791540363 71
```
</details>

---

