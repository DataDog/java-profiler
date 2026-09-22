---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 17:00:42 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1790110505 32
1790110510 32
1790110515 32
1790110520 32
1790110525 32
1790110530 32
1790110535 32
1790110540 32
1790110545 32
1790110550 32
1790110555 32
1790110560 32
1790110565 32
1790110570 32
1790110575 32
1790110580 32
1790110585 32
1790110590 32
1790110595 32
1790110600 32
```
</details>

---

