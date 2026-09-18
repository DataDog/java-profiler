---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 02:28:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1789712655 92
1789712660 92
1789712665 90
1789712670 90
1789712675 90
1789712680 90
1789712685 92
1789712690 92
1789712695 96
1789712700 96
1789712705 96
1789712710 96
1789712715 96
1789712720 96
1789712725 96
1789712730 96
1789712735 96
1789712740 96
1789712745 96
1789712750 96
```
</details>

---

