---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 11:00:42 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 13-30 cores)</summary>

```
1793721209 15
1793721214 15
1793721219 15
1793721224 15
1793721229 15
1793721234 15
1793721239 15
1793721244 15
1793721249 15
1793721254 15
1793721259 15
1793721264 15
1793721269 15
1793721274 15
1793721279 13
1793721284 13
1793721289 30
1793721294 30
1793721299 30
1793721304 30
```
</details>

---

