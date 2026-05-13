---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-13 07:32:05 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 954 |
| Sample Rate | 15.90/sec |
| Health Score | 994% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 49-53 cores)</summary>

```
1778671564 53
1778671569 53
1778671574 53
1778671579 53
1778671584 53
1778671589 53
1778671594 53
1778671599 49
1778671604 49
1778671609 49
1778671614 49
1778671619 49
1778671624 49
1778671629 49
1778671634 49
1778671639 49
1778671644 49
1778671649 49
1778671654 49
1778671659 49
```
</details>

---

