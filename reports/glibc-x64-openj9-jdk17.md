---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 07:31:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 18-46 cores)</summary>

```
1790767621 18
1790767626 18
1790767631 18
1790767636 18
1790767641 18
1790767646 18
1790767651 18
1790767656 18
1790767661 18
1790767666 18
1790767671 18
1790767676 18
1790767681 18
1790767686 18
1790767691 18
1790767696 26
1790767701 26
1790767706 46
1790767711 46
1790767716 46
```
</details>

---

