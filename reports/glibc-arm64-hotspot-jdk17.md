---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-01 14:34:46 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 13 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1788287371 46
1788287376 46
1788287381 46
1788287386 46
1788287391 46
1788287396 46
1788287401 46
1788287406 41
1788287412 41
1788287417 41
1788287422 41
1788287427 41
1788287432 41
1788287437 41
1788287442 41
1788287447 41
1788287452 41
1788287457 46
1788287462 46
1788287467 46
```
</details>

---

