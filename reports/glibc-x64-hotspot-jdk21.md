---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:15:29 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 50-65 cores)</summary>

```
1794582680 56
1794582685 56
1794582690 56
1794582695 56
1794582700 54
1794582705 54
1794582710 54
1794582715 54
1794582720 54
1794582725 54
1794582730 54
1794582735 50
1794582740 50
1794582745 54
1794582750 54
1794582755 54
1794582760 54
1794582765 56
1794582770 56
1794582775 56
```
</details>

---

