---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:44:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1794843597 96
1794843602 96
1794843607 96
1794843612 96
1794843617 96
1794843622 96
1794843627 96
1794843632 94
1794843637 94
1794843642 94
1794843647 94
1794843652 94
1794843657 94
1794843662 94
1794843667 94
1794843672 94
1794843677 94
1794843682 94
1794843687 94
1794843692 94
```
</details>

---

