---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 06:16:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 55-76 cores)</summary>

```
1792145527 58
1792145532 58
1792145537 58
1792145542 58
1792145547 58
1792145552 58
1792145557 76
1792145562 76
1792145567 76
1792145572 76
1792145577 76
1792145582 76
1792145587 76
1792145592 76
1792145597 76
1792145602 76
1792145607 76
1792145612 76
1792145617 55
1792145622 55
```
</details>

---

