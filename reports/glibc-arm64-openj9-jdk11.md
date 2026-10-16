---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 06:16:39 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1792145520 27
1792145525 22
1792145530 22
1792145535 22
1792145540 22
1792145546 22
1792145551 22
1792145556 22
1792145561 22
1792145566 22
1792145571 22
1792145576 22
1792145581 22
1792145586 22
1792145591 22
1792145596 22
1792145601 22
1792145606 22
1792145611 22
1792145616 22
```
</details>

---

