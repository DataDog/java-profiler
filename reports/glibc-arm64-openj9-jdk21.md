---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 15:17:25 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790795619 40
1790795624 40
1790795629 40
1790795634 40
1790795639 40
1790795644 40
1790795649 40
1790795654 40
1790795659 40
1790795664 40
1790795669 40
1790795674 40
1790795679 40
1790795684 40
1790795689 40
1790795694 40
1790795699 40
1790795704 40
1790795709 40
1790795714 40
```
</details>

---

