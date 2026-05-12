---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 09:20:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778591638 64
1778591643 64
1778591648 64
1778591653 64
1778591658 64
1778591663 64
1778591668 64
1778591673 64
1778591678 64
1778591683 64
1778591688 64
1778591693 64
1778591698 64
1778591703 64
1778591708 64
1778591713 64
1778591718 64
1778591723 64
1778591728 64
1778591733 64
```
</details>

---

