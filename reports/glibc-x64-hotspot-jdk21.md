---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-08 14:27:51 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 28-47 cores)</summary>

```
1794165840 32
1794165845 32
1794165850 32
1794165855 32
1794165860 32
1794165865 32
1794165870 28
1794165875 28
1794165880 28
1794165885 28
1794165890 28
1794165895 28
1794165900 28
1794165905 28
1794165910 30
1794165915 30
1794165920 28
1794165925 28
1794165930 28
1794165935 28
```
</details>

---

