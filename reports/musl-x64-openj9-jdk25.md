---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 19:15:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 50-78 cores)</summary>

```
1793142526 50
1793142531 50
1793142536 50
1793142541 55
1793142546 55
1793142551 55
1793142556 55
1793142561 55
1793142566 55
1793142571 55
1793142576 55
1793142581 55
1793142586 55
1793142591 55
1793142596 55
1793142601 78
1793142606 78
1793142611 78
1793142616 78
1793142621 78
```
</details>

---

