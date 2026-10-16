---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-16 06:16:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1792145527 87
1792145532 87
1792145537 87
1792145542 87
1792145547 87
1792145552 87
1792145557 87
1792145562 87
1792145567 89
1792145572 89
1792145577 89
1792145582 89
1792145587 89
1792145592 89
1792145597 89
1792145602 89
1792145607 89
1792145612 89
1792145617 89
1792145622 89
```
</details>

---

