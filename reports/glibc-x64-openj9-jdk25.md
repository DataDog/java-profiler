---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-28 11:27:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 49-58 cores)</summary>

```
1779981596 54
1779981601 54
1779981606 54
1779981611 54
1779981616 54
1779981621 49
1779981626 49
1779981631 49
1779981636 58
1779981641 58
1779981646 56
1779981651 56
1779981656 58
1779981661 58
1779981666 58
1779981671 58
1779981676 58
1779981681 58
1779981686 58
1779981691 53
```
</details>

---

