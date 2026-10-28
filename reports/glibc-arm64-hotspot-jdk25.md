---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:14:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 8 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1793185471 45
1793185476 45
1793185481 45
1793185486 46
1793185491 46
1793185496 46
1793185501 46
1793185506 46
1793185511 46
1793185516 46
1793185521 46
1793185526 46
1793185531 46
1793185536 46
1793185541 46
1793185546 46
1793185551 46
1793185556 46
1793185561 46
1793185566 48
```
</details>

---

