---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-13 11:08:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 14.40/sec |
| Health Score | 900% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 57-62 cores)</summary>

```
1778684555 62
1778684560 62
1778684565 62
1778684570 62
1778684575 62
1778684580 57
1778684585 57
1778684590 57
1778684595 57
1778684600 57
1778684605 57
1778684610 57
1778684615 57
1778684620 57
1778684625 57
1778684630 57
1778684635 57
1778684640 57
1778684645 57
1778684650 57
```
</details>

---

