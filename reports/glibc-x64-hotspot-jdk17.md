---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-31 00:49:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1788151531 17
1788151536 17
1788151541 17
1788151546 17
1788151551 17
1788151556 17
1788151561 17
1788151566 17
1788151571 15
1788151576 15
1788151581 15
1788151586 15
1788151591 15
1788151596 15
1788151601 15
1788151606 15
1788151611 17
1788151616 17
1788151621 17
1788151626 17
```
</details>

---

