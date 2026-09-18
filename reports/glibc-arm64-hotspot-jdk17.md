---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:27:47 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 14-31 cores)</summary>

```
1789737676 14
1789737681 14
1789737686 14
1789737691 14
1789737696 14
1789737701 14
1789737706 14
1789737711 14
1789737716 14
1789737721 31
1789737726 31
1789737731 14
1789737736 14
1789737741 14
1789737746 14
1789737751 14
1789737756 14
1789737761 14
1789737766 14
1789737771 14
```
</details>

---

