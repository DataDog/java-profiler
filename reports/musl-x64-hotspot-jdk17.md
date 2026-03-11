---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-11 14:08:00 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 78-84 cores)</summary>

```
1773252134 78
1773252139 80
1773252144 80
1773252149 80
1773252154 80
1773252159 80
1773252164 80
1773252169 80
1773252174 83
1773252179 83
1773252184 83
1773252189 83
1773252194 81
1773252199 81
1773252204 81
1773252209 83
1773252214 83
1773252219 83
1773252224 83
1773252229 83
```
</details>

---

