---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 14:01:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1044 |
| Sample Rate | 17.40/sec |
| Health Score | 1087% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 80-83 cores)</summary>

```
1795200967 83
1795200972 83
1795200977 83
1795200982 83
1795200987 83
1795200992 83
1795200997 83
1795201002 83
1795201007 83
1795201012 83
1795201017 83
1795201022 83
1795201027 83
1795201032 83
1795201037 83
1795201042 83
1795201047 83
1795201052 83
1795201057 80
1795201062 80
```
</details>

---

