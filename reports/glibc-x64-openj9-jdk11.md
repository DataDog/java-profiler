---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 10:24:27 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 87-96 cores)</summary>

```
1790864323 87
1790864328 87
1790864333 89
1790864338 89
1790864343 89
1790864348 89
1790864353 89
1790864358 89
1790864363 89
1790864368 89
1790864373 89
1790864378 89
1790864383 89
1790864388 89
1790864393 89
1790864398 91
1790864403 91
1790864408 91
1790864413 91
1790864418 93
```
</details>

---

