---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-11 08:50:42 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 21-35 cores)</summary>

```
1773232953 24
1773232958 24
1773232963 24
1773232968 24
1773232973 24
1773232978 30
1773232983 30
1773232988 30
1773232993 30
1773232998 35
1773233003 35
1773233008 35
1773233013 35
1773233018 35
1773233023 35
1773233028 35
1773233033 35
1773233038 35
1773233043 35
1773233048 35
```
</details>

---

