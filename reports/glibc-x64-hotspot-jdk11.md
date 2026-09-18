---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 898 |
| Sample Rate | 14.97/sec |
| Health Score | 936% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1789737701 32
1789737706 32
1789737711 32
1789737716 32
1789737721 32
1789737726 32
1789737731 32
1789737736 32
1789737741 32
1789737746 32
1789737751 32
1789737756 32
1789737761 32
1789737766 32
1789737771 32
1789737776 32
1789737781 32
1789737786 32
1789737791 32
1789737796 32
```
</details>

---

