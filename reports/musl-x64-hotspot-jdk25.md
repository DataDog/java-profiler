---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-12 10:27:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 11 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 13 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1773325355 92
1773325360 92
1773325365 92
1773325370 92
1773325375 96
1773325380 96
1773325385 96
1773325390 96
1773325395 96
1773325400 96
1773325405 96
1773325410 96
1773325415 96
1773325420 96
1773325425 96
1773325430 96
1773325435 96
1773325440 96
1773325445 96
1773325450 96
```
</details>

---

