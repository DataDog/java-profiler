---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 09:20:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (5 unique values: 60-96 cores)</summary>

```
1778591620 60
1778591625 60
1778591630 60
1778591635 60
1778591640 60
1778591645 60
1778591650 60
1778591655 60
1778591660 60
1778591665 60
1778591670 60
1778591675 87
1778591680 87
1778591685 87
1778591690 87
1778591695 96
1778591700 96
1778591705 96
1778591710 96
1778591715 91
```
</details>

---

