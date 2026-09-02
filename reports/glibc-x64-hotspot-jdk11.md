---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 13:35:50 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 939 |
| Sample Rate | 15.65/sec |
| Health Score | 978% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 77-81 cores)</summary>

```
1788369985 81
1788369990 81
1788369995 81
1788370000 81
1788370005 77
1788370010 77
1788370015 77
1788370020 77
1788370025 77
1788370030 77
1788370035 77
1788370040 77
1788370045 77
1788370050 77
1788370055 77
1788370060 77
1788370065 77
1788370070 77
1788370075 77
1788370080 77
```
</details>

---

