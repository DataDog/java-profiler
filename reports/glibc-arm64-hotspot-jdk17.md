---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:14:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 7 |
| Allocations | 90 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1793185463 39
1793185468 39
1793185473 39
1793185478 39
1793185483 39
1793185488 39
1793185493 39
1793185498 39
1793185503 39
1793185508 39
1793185513 39
1793185518 51
1793185523 51
1793185528 51
1793185533 51
1793185538 51
1793185543 51
1793185548 51
1793185553 51
1793185558 51
```
</details>

---

