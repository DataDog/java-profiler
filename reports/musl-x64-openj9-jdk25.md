---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 09:44:16 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 42-61 cores)</summary>

```
1792676401 44
1792676406 44
1792676411 44
1792676416 44
1792676421 44
1792676426 44
1792676431 44
1792676436 44
1792676441 44
1792676446 44
1792676451 44
1792676456 44
1792676461 44
1792676466 44
1792676471 44
1792676476 44
1792676481 42
1792676486 42
1792676491 61
1792676496 61
```
</details>

---

