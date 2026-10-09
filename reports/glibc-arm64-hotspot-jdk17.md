---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 06:10:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 14 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 41-52 cores)</summary>

```
1791540310 41
1791540315 41
1791540320 41
1791540325 41
1791540330 41
1791540335 52
1791540340 52
1791540345 52
1791540350 52
1791540355 52
1791540360 52
1791540365 52
1791540370 52
1791540375 52
1791540380 52
1791540385 52
1791540390 52
1791540395 52
1791540400 52
1791540405 52
```
</details>

---

