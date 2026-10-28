---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:14:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 306 |
| Sample Rate | 5.10/sec |
| Health Score | 319% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1793185575 22
1793185580 22
1793185585 22
1793185590 22
1793185595 22
1793185600 22
1793185605 22
1793185610 22
1793185615 22
1793185620 27
1793185625 27
1793185630 27
1793185635 27
1793185640 27
1793185645 27
1793185650 27
1793185655 27
1793185660 27
1793185665 27
1793185670 27
```
</details>

---

