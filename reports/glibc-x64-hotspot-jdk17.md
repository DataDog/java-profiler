---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:49:36 EST

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (4 unique values: 17-48 cores)</summary>

```
1795430715 17
1795430720 17
1795430725 17
1795430730 17
1795430735 17
1795430740 17
1795430745 37
1795430750 37
1795430755 37
1795430760 37
1795430765 37
1795430770 37
1795430775 37
1795430780 37
1795430785 40
1795430790 40
1795430795 37
1795430800 37
1795430805 37
1795430810 37
```
</details>

---

