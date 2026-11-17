---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 06:43:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (2 unique values: 10-13 cores)</summary>

```
1794915475 10
1794915480 10
1794915485 10
1794915490 10
1794915495 10
1794915500 10
1794915505 10
1794915510 10
1794915515 13
1794915520 13
1794915525 13
1794915530 13
1794915536 13
1794915541 13
1794915546 13
1794915551 13
1794915556 13
1794915561 13
1794915566 13
1794915571 13
```
</details>

---

