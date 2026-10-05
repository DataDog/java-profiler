---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 06:41:11 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 839 |
| Sample Rate | 13.98/sec |
| Health Score | 874% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 79-88 cores)</summary>

```
1791196539 87
1791196544 87
1791196549 87
1791196554 87
1791196559 87
1791196564 87
1791196569 87
1791196574 87
1791196579 87
1791196584 87
1791196589 79
1791196594 79
1791196599 79
1791196604 79
1791196609 79
1791196614 85
1791196619 85
1791196624 88
1791196629 88
1791196634 88
```
</details>

---

