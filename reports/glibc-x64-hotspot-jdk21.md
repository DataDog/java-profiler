---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 05:23:32 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 41-68 cores)</summary>

```
1773220569 53
1773220574 63
1773220579 63
1773220584 68
1773220589 68
1773220594 46
1773220599 46
1773220604 46
1773220609 46
1773220614 46
1773220619 46
1773220624 46
1773220629 46
1773220634 41
1773220639 41
1773220644 41
1773220649 41
1773220654 41
1773220659 41
1773220664 41
```
</details>

---

