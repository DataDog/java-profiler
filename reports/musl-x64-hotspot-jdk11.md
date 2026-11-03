---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:25:57 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 72-85 cores)</summary>

```
1793722736 72
1793722741 72
1793722746 72
1793722751 72
1793722756 72
1793722761 81
1793722766 81
1793722771 81
1793722776 83
1793722781 83
1793722786 83
1793722791 83
1793722796 85
1793722801 85
1793722806 85
1793722811 85
1793722817 85
1793722822 85
1793722827 85
1793722832 85
```
</details>

---

