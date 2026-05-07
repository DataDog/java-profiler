---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 09:00:14 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 872 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (5 unique values: 67-85 cores)</summary>

```
1778158390 85
1778158395 85
1778158400 85
1778158405 85
1778158410 85
1778158415 81
1778158420 81
1778158425 81
1778158430 81
1778158435 71
1778158440 71
1778158445 71
1778158450 71
1778158455 71
1778158460 71
1778158465 71
1778158471 71
1778158476 71
1778158481 71
1778158486 67
```
</details>

---

