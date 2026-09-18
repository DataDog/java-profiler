---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 43-74 cores)</summary>

```
1789737700 54
1789737705 54
1789737710 54
1789737715 74
1789737721 74
1789737726 74
1789737731 51
1789737736 51
1789737741 51
1789737746 51
1789737751 51
1789737756 51
1789737761 51
1789737766 51
1789737771 51
1789737776 51
1789737781 51
1789737786 51
1789737791 43
1789737796 43
```
</details>

---

