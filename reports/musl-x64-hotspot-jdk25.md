---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:12:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 76-80 cores)</summary>

```
1793185655 80
1793185660 80
1793185665 80
1793185670 80
1793185675 80
1793185680 80
1793185685 80
1793185690 80
1793185695 80
1793185700 80
1793185705 80
1793185710 80
1793185715 78
1793185720 78
1793185725 78
1793185730 78
1793185735 78
1793185740 78
1793185745 76
1793185750 76
```
</details>

---

