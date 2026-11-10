---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 13:23:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 451 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 36-47 cores)</summary>

```
1794334680 36
1794334685 36
1794334690 36
1794334695 36
1794334700 36
1794334705 36
1794334710 36
1794334715 36
1794334720 36
1794334725 36
1794334730 36
1794334735 36
1794334740 38
1794334745 38
1794334750 38
1794334755 38
1794334760 38
1794334765 38
1794334770 47
1794334775 47
```
</details>

---

