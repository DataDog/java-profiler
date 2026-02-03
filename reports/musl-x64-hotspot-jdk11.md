---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 05:16:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1014 |
| Sample Rate | 16.90/sec |
| Health Score | 1056% |
| Threads | 11 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (4 unique values: 88-96 cores)</summary>

```
1770113620 96
1770113625 96
1770113630 96
1770113635 90
1770113640 90
1770113645 90
1770113650 90
1770113655 90
1770113660 90
1770113665 90
1770113670 90
1770113675 90
1770113680 90
1770113685 92
1770113690 92
1770113695 92
1770113700 92
1770113705 90
1770113710 90
1770113715 90
```
</details>

---

