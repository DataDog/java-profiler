---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-05 07:14:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1793880504 33
1793880509 33
1793880514 33
1793880519 43
1793880524 43
1793880529 41
1793880534 41
1793880539 41
1793880544 41
1793880549 41
1793880554 41
1793880559 41
1793880564 41
1793880569 41
1793880574 43
1793880579 43
1793880584 43
1793880589 43
1793880594 43
1793880599 43
```
</details>

---

