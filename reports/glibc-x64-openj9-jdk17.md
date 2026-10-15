---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-15 03:56:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 8 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1792050686 27
1792050691 27
1792050696 27
1792050701 27
1792050706 27
1792050711 29
1792050716 29
1792050721 29
1792050726 29
1792050731 29
1792050736 29
1792050741 29
1792050746 29
1792050751 29
1792050756 29
1792050761 29
1792050766 29
1792050771 29
1792050776 29
1792050781 29
```
</details>

---

