---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 13:40:55 EDT

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
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1787074513 96
1787074518 96
1787074523 94
1787074528 94
1787074533 94
1787074538 94
1787074543 94
1787074548 94
1787074553 92
1787074558 92
1787074563 92
1787074568 92
1787074573 92
1787074578 92
1787074583 94
1787074588 94
1787074593 94
1787074598 94
1787074603 94
1787074608 94
```
</details>

---

