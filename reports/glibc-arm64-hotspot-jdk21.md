---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 09:20:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 33-43 cores)</summary>

```
1791465267 43
1791465272 43
1791465277 38
1791465282 38
1791465287 33
1791465292 33
1791465297 38
1791465302 38
1791465307 38
1791465312 38
1791465317 38
1791465322 38
1791465327 38
1791465332 38
1791465337 43
1791465342 43
1791465347 43
1791465352 43
1791465357 43
1791465362 43
```
</details>

---

