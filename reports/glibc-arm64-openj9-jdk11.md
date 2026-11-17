---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 06:43:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 11 |
| Allocations | 202 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794915538 41
1794915544 41
1794915549 41
1794915554 41
1794915559 41
1794915564 41
1794915569 41
1794915574 41
1794915579 41
1794915584 41
1794915589 41
1794915594 41
1794915599 46
1794915604 46
1794915609 46
1794915614 46
1794915619 46
1794915624 46
1794915629 46
1794915634 46
```
</details>

---

