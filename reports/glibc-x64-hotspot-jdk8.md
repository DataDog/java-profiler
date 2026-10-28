---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:12:34 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793185680 30
1793185685 30
1793185690 30
1793185695 30
1793185700 30
1793185705 30
1793185710 30
1793185715 30
1793185720 30
1793185725 32
1793185730 32
1793185735 32
1793185740 32
1793185745 32
1793185750 32
1793185755 32
1793185760 32
1793185765 32
1793185770 32
1793185775 32
```
</details>

---

