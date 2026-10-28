---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:14:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 14 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1793185485 39
1793185490 39
1793185496 39
1793185501 39
1793185506 39
1793185511 39
1793185516 51
1793185521 51
1793185526 51
1793185531 51
1793185536 51
1793185541 51
1793185546 51
1793185551 51
1793185556 51
1793185561 51
1793185566 51
1793185571 51
1793185576 51
1793185581 51
```
</details>

---

