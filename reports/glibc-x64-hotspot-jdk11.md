---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:42:59 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1026 |
| Sample Rate | 17.10/sec |
| Health Score | 1069% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 64-69 cores)</summary>

```
1778150305 64
1778150310 64
1778150315 64
1778150320 64
1778150325 69
1778150330 69
1778150335 69
1778150340 64
1778150345 64
1778150350 65
1778150355 65
1778150360 65
1778150365 65
1778150370 65
1778150375 65
1778150380 65
1778150385 65
1778150390 65
1778150395 65
1778150400 65
```
</details>

---

