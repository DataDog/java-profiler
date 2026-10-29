---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 11:53:30 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 11 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1793288635 61
1793288640 61
1793288645 61
1793288650 61
1793288655 61
1793288660 61
1793288665 61
1793288671 59
1793288676 59
1793288681 59
1793288686 59
1793288691 59
1793288696 59
1793288701 59
1793288706 59
1793288711 59
1793288716 59
1793288721 59
1793288726 59
1793288731 59
```
</details>

---

