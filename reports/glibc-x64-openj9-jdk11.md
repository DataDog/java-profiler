---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:20:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 68-93 cores)</summary>

```
1790777656 68
1790777661 68
1790777666 68
1790777671 68
1790777676 68
1790777681 68
1790777686 68
1790777691 68
1790777696 68
1790777701 68
1790777706 68
1790777711 71
1790777716 71
1790777721 71
1790777726 71
1790777731 91
1790777736 91
1790777741 91
1790777746 91
1790777751 91
```
</details>

---

