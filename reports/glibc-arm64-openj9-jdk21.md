---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 07:14:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 20-25 cores)</summary>

```
1793880539 20
1793880544 20
1793880549 20
1793880554 20
1793880559 20
1793880564 25
1793880569 25
1793880574 25
1793880579 25
1793880584 25
1793880589 25
1793880594 25
1793880599 25
1793880604 25
1793880609 25
1793880614 25
1793880619 25
1793880624 25
1793880629 25
1793880634 25
```
</details>

---

