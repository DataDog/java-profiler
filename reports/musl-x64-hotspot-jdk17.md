---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-24 08:33:46 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 909 |
| Sample Rate | 15.15/sec |
| Health Score | 947% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1777033634 22
1777033639 22
1777033644 22
1777033649 22
1777033654 22
1777033659 22
1777033664 27
1777033669 27
1777033674 27
1777033679 27
1777033684 27
1777033689 27
1777033694 27
1777033699 27
1777033704 27
1777033709 27
1777033714 27
1777033719 27
1777033724 27
1777033729 27
```
</details>

---

