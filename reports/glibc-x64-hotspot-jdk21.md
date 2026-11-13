---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:44:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794584433 94
1794584439 94
1794584444 96
1794584449 96
1794584454 96
1794584459 96
1794584464 96
1794584469 96
1794584474 96
1794584479 96
1794584484 96
1794584489 96
1794584494 96
1794584499 96
1794584504 96
1794584509 96
1794584514 94
1794584519 94
1794584524 94
1794584529 94
```
</details>

---

