---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 06:25:15 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 14 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794914418 51
1794914423 51
1794914428 51
1794914433 51
1794914438 51
1794914443 51
1794914448 46
1794914453 46
1794914458 46
1794914463 46
1794914468 46
1794914473 46
1794914478 46
1794914483 46
1794914488 46
1794914493 46
1794914498 46
1794914503 46
1794914508 46
1794914513 46
```
</details>

---

