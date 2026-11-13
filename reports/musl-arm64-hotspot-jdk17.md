---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 12:12:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794589620 44
1794589625 44
1794589630 44
1794589635 44
1794589640 44
1794589645 44
1794589650 44
1794589655 44
1794589660 44
1794589665 44
1794589670 44
1794589675 44
1794589680 44
1794589685 48
1794589690 48
1794589695 48
1794589700 48
1794589705 48
1794589710 48
1794589715 48
```
</details>

---

