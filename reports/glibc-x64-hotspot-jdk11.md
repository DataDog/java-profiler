---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 17:16:30 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
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
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 897 |
| Sample Rate | 14.95/sec |
| Health Score | 934% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 50-59 cores)</summary>

```
1794435125 54
1794435130 54
1794435135 54
1794435140 54
1794435145 54
1794435150 54
1794435155 54
1794435160 52
1794435165 52
1794435170 52
1794435175 50
1794435180 50
1794435185 50
1794435190 50
1794435195 50
1794435200 50
1794435205 50
1794435210 50
1794435215 50
1794435220 50
```
</details>

---

