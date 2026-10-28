---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:17:16 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (5 unique values: 70-94 cores)</summary>

```
1793185725 70
1793185730 70
1793185735 70
1793185740 70
1793185745 70
1793185750 70
1793185755 70
1793185760 70
1793185765 70
1793185770 70
1793185775 70
1793185780 72
1793185785 72
1793185790 72
1793185795 72
1793185800 74
1793185805 74
1793185810 74
1793185815 74
1793185820 74
```
</details>

---

