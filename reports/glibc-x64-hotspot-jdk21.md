---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-31 00:49:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (6 unique values: 50-63 cores)</summary>

```
1788151526 60
1788151531 60
1788151536 60
1788151541 60
1788151546 58
1788151551 58
1788151556 63
1788151561 63
1788151566 63
1788151571 63
1788151576 61
1788151582 61
1788151587 61
1788151592 61
1788151597 61
1788151602 61
1788151607 61
1788151612 61
1788151617 61
1788151622 61
```
</details>

---

