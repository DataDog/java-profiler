---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-26 09:45:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 66-88 cores)</summary>

```
1787751594 68
1787751599 68
1787751604 68
1787751609 68
1787751614 68
1787751619 68
1787751624 68
1787751629 68
1787751634 68
1787751639 68
1787751644 68
1787751649 68
1787751654 66
1787751659 66
1787751664 66
1787751669 66
1787751674 66
1787751679 66
1787751684 66
1787751689 66
```
</details>

---

