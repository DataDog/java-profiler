---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:06:33 EDT

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 8 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 8-19 cores)</summary>

```
1790168555 8
1790168560 8
1790168565 8
1790168570 8
1790168575 10
1790168580 10
1790168585 10
1790168590 10
1790168596 9
1790168601 9
1790168606 9
1790168611 9
1790168616 9
1790168621 9
1790168626 9
1790168631 9
1790168636 9
1790168641 9
1790168646 9
1790168651 19
```
</details>

---

