---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 05:30:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (1 unique values: 21-21 cores)</summary>

```
1794997524 21
1794997529 21
1794997534 21
1794997539 21
1794997544 21
1794997549 21
1794997554 21
1794997559 21
1794997564 21
1794997569 21
1794997574 21
1794997579 21
1794997584 21
1794997589 21
1794997594 21
1794997599 21
1794997604 21
1794997609 21
1794997614 21
1794997619 21
```
</details>

---

