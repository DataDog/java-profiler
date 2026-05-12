---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 04:02:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 65-67 cores)</summary>

```
1778572550 65
1778572555 65
1778572560 65
1778572565 65
1778572570 65
1778572575 65
1778572580 65
1778572585 65
1778572590 65
1778572595 65
1778572600 65
1778572605 65
1778572610 67
1778572615 67
1778572620 67
1778572625 65
1778572630 65
1778572635 65
1778572640 65
1778572645 65
```
</details>

---

