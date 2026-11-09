---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 15:36:43 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 14 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (5 unique values: 42-46 cores)</summary>

```
1794256293 44
1794256298 44
1794256303 44
1794256308 44
1794256313 44
1794256318 44
1794256323 44
1794256328 44
1794256333 44
1794256338 44
1794256343 44
1794256348 44
1794256353 44
1794256358 44
1794256363 44
1794256368 45
1794256373 45
1794256378 45
1794256383 45
1794256388 46
```
</details>

---

