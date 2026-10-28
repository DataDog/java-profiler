---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:12:34 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 311 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1793185710 76
1793185715 76
1793185720 76
1793185725 76
1793185730 76
1793185735 76
1793185740 76
1793185745 76
1793185750 76
1793185755 76
1793185760 76
1793185765 76
1793185770 76
1793185775 76
1793185780 76
1793185785 76
1793185790 74
1793185795 74
1793185800 74
1793185805 74
```
</details>

---

