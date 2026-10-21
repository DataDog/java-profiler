---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 13:20:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (4 unique values: 44-60 cores)</summary>

```
1792602511 49
1792602516 44
1792602521 44
1792602526 55
1792602531 55
1792602536 55
1792602541 55
1792602546 55
1792602551 55
1792602556 55
1792602561 55
1792602567 55
1792602572 55
1792602577 55
1792602582 55
1792602587 60
1792602592 60
1792602597 60
1792602602 60
1792602607 60
```
</details>

---

