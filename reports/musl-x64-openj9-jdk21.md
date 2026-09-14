---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-09-14 12:04:49 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 88-96 cores)</summary>

```
1789401514 90
1789401519 90
1789401524 90
1789401529 90
1789401534 90
1789401539 88
1789401544 88
1789401549 88
1789401554 88
1789401559 88
1789401564 88
1789401569 88
1789401574 88
1789401579 88
1789401584 90
1789401589 90
1789401594 90
1789401599 92
1789401604 92
1789401610 92
```
</details>

---

