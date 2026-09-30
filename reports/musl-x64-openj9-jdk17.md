---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 10:20:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 8 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1790777686 32
1790777691 32
1790777696 32
1790777701 32
1790777706 32
1790777711 32
1790777716 32
1790777721 32
1790777726 32
1790777731 32
1790777736 29
1790777741 29
1790777746 29
1790777751 29
1790777756 29
1790777761 29
1790777766 29
1790777771 29
1790777776 29
1790777781 29
```
</details>

---

