---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:27:50 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 861 |
| Sample Rate | 14.35/sec |
| Health Score | 897% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 35-56 cores)</summary>

```
1789737671 39
1789737676 39
1789737681 39
1789737686 39
1789737691 56
1789737696 56
1789737701 35
1789737706 35
1789737711 35
1789737716 35
1789737721 35
1789737726 35
1789737731 35
1789737736 35
1789737741 35
1789737746 35
1789737751 35
1789737756 35
1789737761 35
1789737766 35
```
</details>

---

