---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-14 12:04:49 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 82-96 cores)</summary>

```
1789401508 96
1789401513 96
1789401518 96
1789401523 96
1789401528 96
1789401533 94
1789401538 94
1789401543 94
1789401548 94
1789401553 92
1789401558 92
1789401563 92
1789401568 92
1789401573 92
1789401578 82
1789401583 82
1789401588 82
1789401593 82
1789401598 82
1789401603 82
```
</details>

---

