---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:12:35 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (5 unique values: 72-94 cores)</summary>

```
1793185670 79
1793185675 79
1793185680 77
1793185685 77
1793185690 94
1793185695 94
1793185700 74
1793185705 74
1793185710 74
1793185715 74
1793185720 74
1793185725 74
1793185730 72
1793185735 72
1793185740 72
1793185745 72
1793185750 72
1793185755 72
1793185760 72
1793185765 72
```
</details>

---

