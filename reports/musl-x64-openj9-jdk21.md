---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 10:59:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 63-96 cores)</summary>

```
1792075882 63
1792075887 63
1792075892 63
1792075897 90
1792075902 90
1792075907 90
1792075912 90
1792075917 90
1792075922 90
1792075927 90
1792075932 90
1792075937 90
1792075942 90
1792075947 90
1792075952 90
1792075957 92
1792075962 92
1792075967 92
1792075972 92
1792075977 92
```
</details>

---

