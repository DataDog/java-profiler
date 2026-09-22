---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 17:00:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790110529 50
1790110534 50
1790110539 50
1790110544 50
1790110549 50
1790110554 50
1790110559 50
1790110564 50
1790110569 50
1790110574 50
1790110579 50
1790110584 50
1790110589 50
1790110594 50
1790110599 50
1790110604 50
1790110609 50
1790110614 50
1790110619 50
1790110624 50
```
</details>

---

