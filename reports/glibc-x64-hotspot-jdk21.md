---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 09:56:09 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 12 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 58-60 cores)</summary>

```
1793890238 58
1793890243 58
1793890248 58
1793890253 58
1793890258 60
1793890263 60
1793890268 60
1793890273 60
1793890278 60
1793890283 60
1793890288 60
1793890293 60
1793890298 58
1793890303 58
1793890308 58
1793890313 59
1793890318 59
1793890323 59
1793890328 59
1793890333 59
```
</details>

---

