---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 06:42:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778582330 64
1778582335 64
1778582340 64
1778582345 64
1778582350 64
1778582355 64
1778582360 64
1778582365 64
1778582370 64
1778582375 64
1778582380 64
1778582385 64
1778582390 64
1778582395 64
1778582400 64
1778582405 64
1778582410 64
1778582415 64
1778582420 64
1778582425 64
```
</details>

---

