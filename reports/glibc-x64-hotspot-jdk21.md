---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 09:37:45 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 46-87 cores)</summary>

```
1794839656 87
1794839661 87
1794839666 87
1794839671 87
1794839676 87
1794839681 87
1794839686 87
1794839691 87
1794839696 87
1794839701 87
1794839706 87
1794839711 87
1794839716 87
1794839721 87
1794839726 87
1794839731 87
1794839736 46
1794839741 46
1794839746 46
1794839751 46
```
</details>

---

