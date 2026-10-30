---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 09:45:20 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1793367632 52
1793367637 52
1793367642 52
1793367647 52
1793367652 52
1793367657 52
1793367662 52
1793367667 52
1793367672 52
1793367677 52
1793367682 52
1793367687 52
1793367692 52
1793367697 52
1793367702 52
1793367707 52
1793367712 52
1793367717 54
1793367722 54
1793367727 54
```
</details>

---

