---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 14:59:46 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (5 unique values: 55-75 cores)</summary>

```
1776279144 75
1776279149 75
1776279154 55
1776279159 55
1776279164 55
1776279169 55
1776279174 55
1776279179 55
1776279184 55
1776279189 55
1776279194 55
1776279199 55
1776279204 55
1776279209 55
1776279214 55
1776279219 55
1776279224 59
1776279229 59
1776279234 57
1776279239 57
```
</details>

---

