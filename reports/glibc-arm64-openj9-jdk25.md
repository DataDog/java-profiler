---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 07:43:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1792496392 46
1792496397 46
1792496402 46
1792496407 46
1792496412 46
1792496417 46
1792496422 46
1792496427 46
1792496432 46
1792496437 46
1792496442 46
1792496447 46
1792496452 46
1792496457 46
1792496462 46
1792496467 46
1792496472 46
1792496477 48
1792496482 48
1792496487 48
```
</details>

---

