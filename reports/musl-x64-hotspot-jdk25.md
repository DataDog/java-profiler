---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 09:00:16 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (5 unique values: 75-82 cores)</summary>

```
1778158385 77
1778158390 77
1778158395 77
1778158400 77
1778158405 77
1778158410 77
1778158415 77
1778158420 75
1778158425 75
1778158430 78
1778158435 78
1778158440 78
1778158445 78
1778158450 80
1778158455 80
1778158460 80
1778158465 80
1778158470 82
1778158475 82
1778158480 82
```
</details>

---

