---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:38:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (4 unique values: 57-81 cores)</summary>

```
1789716449 81
1789716454 77
1789716459 77
1789716464 57
1789716469 57
1789716474 57
1789716479 57
1789716484 57
1789716489 57
1789716494 57
1789716499 59
1789716504 59
1789716509 59
1789716514 59
1789716519 59
1789716524 59
1789716529 59
1789716534 59
1789716539 59
1789716544 59
```
</details>

---

