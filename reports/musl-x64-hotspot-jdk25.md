---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-02 12:03:39 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 11 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 14.87/sec |
| Health Score | 929% |
| Threads | 12 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 87-96 cores)</summary>

```
1770051355 87
1770051360 87
1770051365 87
1770051370 87
1770051375 87
1770051380 87
1770051385 87
1770051390 87
1770051395 96
1770051400 96
1770051405 96
1770051410 96
1770051415 96
1770051420 96
1770051425 96
1770051430 96
1770051435 96
1770051440 96
1770051445 94
1770051450 94
```
</details>

---

