---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:39:34 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 75-93 cores)</summary>

```
1793205358 93
1793205363 93
1793205368 93
1793205373 93
1793205378 93
1793205383 93
1793205388 93
1793205393 93
1793205398 93
1793205403 93
1793205408 93
1793205413 93
1793205418 93
1793205423 93
1793205428 93
1793205433 93
1793205438 93
1793205443 75
1793205448 75
1793205453 75
```
</details>

---

