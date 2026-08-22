---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 08:14:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 9 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787400651 48
1787400656 48
1787400661 48
1787400666 48
1787400671 48
1787400676 48
1787400681 48
1787400686 48
1787400691 48
1787400696 48
1787400701 48
1787400706 48
1787400711 48
1787400716 48
1787400721 48
1787400726 43
1787400731 43
1787400736 43
1787400741 43
1787400746 43
```
</details>

---

