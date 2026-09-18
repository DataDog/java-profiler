---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:32:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 13 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (4 unique values: 11-16 cores)</summary>

```
1789737686 11
1789737691 11
1789737696 14
1789737701 14
1789737706 14
1789737711 14
1789737716 14
1789737721 14
1789737726 14
1789737731 14
1789737736 14
1789737741 15
1789737746 15
1789737751 15
1789737756 15
1789737761 16
1789737767 16
1789737772 16
1789737777 16
1789737782 16
```
</details>

---

