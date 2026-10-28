---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:17:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 68-88 cores)</summary>

```
1793185630 70
1793185635 70
1793185640 70
1793185645 70
1793185650 70
1793185655 70
1793185660 70
1793185665 68
1793185670 68
1793185675 68
1793185680 68
1793185685 68
1793185690 68
1793185695 68
1793185700 68
1793185705 88
1793185710 88
1793185715 88
1793185720 88
1793185725 88
```
</details>

---

