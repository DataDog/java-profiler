---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 06:11:49 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 589 |

<details>
<summary>CPU Timeline (4 unique values: 24-32 cores)</summary>

```
1792490636 28
1792490641 25
1792490646 25
1792490651 25
1792490656 25
1792490661 25
1792490666 25
1792490671 25
1792490676 25
1792490681 32
1792490686 32
1792490691 32
1792490696 32
1792490701 32
1792490706 32
1792490711 32
1792490716 32
1792490721 24
1792490726 24
1792490731 24
```
</details>

---

