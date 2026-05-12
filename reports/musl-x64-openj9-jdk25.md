---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:43:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (9 unique values: 57-79 cores)</summary>

```
1778582317 79
1778582322 79
1778582327 79
1778582333 79
1778582338 79
1778582343 74
1778582348 74
1778582353 68
1778582358 68
1778582363 68
1778582368 64
1778582373 64
1778582378 64
1778582383 60
1778582388 60
1778582393 60
1778582398 62
1778582403 62
1778582408 57
1778582413 57
```
</details>

---

