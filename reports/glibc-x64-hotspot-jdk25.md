---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 11:53:28 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 81-88 cores)</summary>

```
1793288696 81
1793288701 81
1793288706 81
1793288711 81
1793288716 81
1793288721 81
1793288726 81
1793288731 81
1793288736 81
1793288741 81
1793288746 81
1793288751 81
1793288756 81
1793288761 81
1793288766 83
1793288771 83
1793288776 83
1793288781 83
1793288786 83
1793288791 83
```
</details>

---

