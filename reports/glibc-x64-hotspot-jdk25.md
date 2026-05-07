---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:54:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 66-84 cores)</summary>

```
1778165310 66
1778165315 67
1778165320 67
1778165325 67
1778165330 67
1778165335 69
1778165340 69
1778165345 84
1778165350 84
1778165355 84
1778165360 84
1778165365 84
1778165370 84
1778165375 84
1778165380 84
1778165385 84
1778165390 84
1778165395 84
1778165400 82
1778165405 82
```
</details>

---

