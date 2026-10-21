---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 13:20:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 567 |

<details>
<summary>CPU Timeline (2 unique values: 71-76 cores)</summary>

```
1792602518 71
1792602523 71
1792602528 71
1792602533 71
1792602538 71
1792602543 71
1792602548 71
1792602553 71
1792602558 71
1792602563 71
1792602568 71
1792602573 71
1792602578 71
1792602583 71
1792602588 71
1792602593 71
1792602598 71
1792602603 76
1792602608 76
1792602613 76
```
</details>

---

