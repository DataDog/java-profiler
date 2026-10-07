---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-07 05:56:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 53-60 cores)</summary>

```
1791366514 53
1791366519 53
1791366524 53
1791366529 53
1791366534 53
1791366539 53
1791366544 58
1791366549 58
1791366554 58
1791366559 58
1791366564 58
1791366569 58
1791366574 56
1791366579 56
1791366584 56
1791366589 56
1791366594 56
1791366599 56
1791366604 56
1791366609 56
```
</details>

---

