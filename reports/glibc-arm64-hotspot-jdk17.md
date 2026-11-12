---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:21:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 331 |
| Sample Rate | 5.52/sec |
| Health Score | 345% |
| Threads | 10 |
| Allocations | 127 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 15 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794507411 48
1794507416 48
1794507422 48
1794507427 48
1794507432 48
1794507437 48
1794507442 48
1794507447 48
1794507452 48
1794507457 48
1794507462 43
1794507467 43
1794507472 43
1794507477 43
1794507482 43
1794507487 43
1794507492 43
1794507497 43
1794507502 43
1794507507 43
```
</details>

---

