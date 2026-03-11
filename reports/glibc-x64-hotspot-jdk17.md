---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-11 05:23:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (4 unique values: 41-45 cores)</summary>

```
1773220705 43
1773220710 42
1773220715 42
1773220720 43
1773220725 43
1773220730 43
1773220735 43
1773220740 43
1773220745 43
1773220750 43
1773220755 43
1773220760 43
1773220765 43
1773220770 43
1773220775 43
1773220780 41
1773220785 41
1773220790 41
1773220795 41
1773220800 45
```
</details>

---

