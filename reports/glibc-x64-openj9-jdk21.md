---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 10:54:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 929 |
| Sample Rate | 15.48/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 72-81 cores)</summary>

```
1778165318 81
1778165323 81
1778165328 81
1778165333 81
1778165338 81
1778165343 81
1778165348 81
1778165353 79
1778165358 79
1778165363 79
1778165368 81
1778165373 81
1778165378 81
1778165383 81
1778165388 81
1778165393 81
1778165398 81
1778165403 81
1778165408 81
1778165413 81
```
</details>

---

