---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 10:54:16 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 83-88 cores)</summary>

```
1778165315 83
1778165320 83
1778165325 83
1778165330 83
1778165335 85
1778165340 85
1778165345 85
1778165350 85
1778165355 85
1778165360 88
1778165365 88
1778165370 88
1778165375 88
1778165380 88
1778165385 88
1778165390 88
1778165395 88
1778165400 88
1778165405 88
1778165410 85
```
</details>

---

