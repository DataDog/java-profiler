---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-15 08:56:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 73-78 cores)</summary>

```
1794750686 73
1794750691 73
1794750696 73
1794750701 73
1794750706 73
1794750711 73
1794750716 73
1794750721 73
1794750726 73
1794750731 73
1794750736 73
1794750741 73
1794750746 73
1794750751 73
1794750756 78
1794750761 78
1794750766 78
1794750771 78
1794750776 78
1794750781 78
```
</details>

---

