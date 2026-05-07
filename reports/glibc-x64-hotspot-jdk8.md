---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-07 10:54:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 65-83 cores)</summary>

```
1778165320 65
1778165325 65
1778165330 67
1778165335 67
1778165340 67
1778165345 67
1778165350 67
1778165355 69
1778165360 69
1778165365 69
1778165370 69
1778165375 75
1778165380 75
1778165385 75
1778165390 83
1778165395 83
1778165400 83
1778165405 83
1778165410 83
1778165415 83
```
</details>

---

