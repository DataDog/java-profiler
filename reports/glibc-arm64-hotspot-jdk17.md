---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-26 01:03:07 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 14 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790398393 38
1790398398 43
1790398403 43
1790398408 43
1790398413 43
1790398418 43
1790398423 43
1790398428 43
1790398433 43
1790398438 43
1790398443 43
1790398448 43
1790398453 43
1790398458 43
1790398463 43
1790398468 43
1790398473 43
1790398478 43
1790398483 43
1790398488 43
```
</details>

---

