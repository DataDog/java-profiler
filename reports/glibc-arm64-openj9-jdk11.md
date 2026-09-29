---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 05:18:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1790673306 46
1790673311 46
1790673316 46
1790673321 46
1790673326 46
1790673331 46
1790673336 46
1790673341 41
1790673346 41
1790673351 41
1790673356 41
1790673361 43
1790673366 43
1790673371 43
1790673376 43
1790673381 43
1790673386 43
1790673391 48
1790673396 48
1790673401 48
```
</details>

---

