---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 11:22:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 71-75 cores)</summary>

```
1793722626 73
1793722631 73
1793722636 73
1793722641 73
1793722646 75
1793722651 75
1793722656 75
1793722661 75
1793722666 75
1793722671 75
1793722676 75
1793722681 75
1793722686 75
1793722692 75
1793722697 75
1793722702 75
1793722707 75
1793722712 75
1793722717 75
1793722722 73
```
</details>

---

