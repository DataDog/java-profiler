---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 08:34:15 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 313 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795613396 85
1795613401 85
1795613406 87
1795613411 87
1795613416 87
1795613421 87
1795613426 87
1795613431 87
1795613436 87
1795613441 87
1795613446 87
1795613451 87
1795613456 87
1795613461 87
1795613466 87
1795613471 87
1795613476 87
1795613481 87
1795613486 87
1795613491 87
```
</details>

---

