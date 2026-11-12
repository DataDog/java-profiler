---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 07:47:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 64-79 cores)</summary>

```
1794487370 79
1794487375 79
1794487380 79
1794487385 79
1794487390 79
1794487395 79
1794487400 79
1794487405 79
1794487410 79
1794487415 79
1794487420 79
1794487425 79
1794487430 68
1794487435 68
1794487440 68
1794487445 68
1794487450 68
1794487455 68
1794487460 68
1794487465 68
```
</details>

---

