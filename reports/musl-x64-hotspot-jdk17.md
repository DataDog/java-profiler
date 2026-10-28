---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:12:35 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1793185681 47
1793185686 47
1793185691 47
1793185696 47
1793185701 47
1793185706 47
1793185711 47
1793185716 47
1793185721 47
1793185726 47
1793185731 45
1793185736 45
1793185741 45
1793185746 45
1793185751 45
1793185756 45
1793185761 45
1793185766 45
1793185771 45
1793185776 45
```
</details>

---

