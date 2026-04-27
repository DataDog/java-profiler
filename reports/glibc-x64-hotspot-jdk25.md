---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-27 14:34:06 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 75-88 cores)</summary>

```
1777314525 88
1777314530 88
1777314535 88
1777314540 88
1777314545 88
1777314550 84
1777314555 84
1777314560 84
1777314565 84
1777314570 84
1777314575 84
1777314580 84
1777314585 84
1777314590 84
1777314595 84
1777314600 84
1777314605 84
1777314610 84
1777314615 84
1777314620 84
```
</details>

---

