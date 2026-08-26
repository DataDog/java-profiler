---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-26 09:45:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1787751589 38
1787751594 43
1787751599 43
1787751604 48
1787751609 48
1787751614 48
1787751619 48
1787751624 48
1787751629 48
1787751634 48
1787751639 48
1787751644 48
1787751649 48
1787751654 48
1787751659 48
1787751664 48
1787751669 48
1787751674 48
1787751679 48
1787751684 48
```
</details>

---

