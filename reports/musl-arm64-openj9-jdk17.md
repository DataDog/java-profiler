---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 20:12:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 10 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1787443567 18
1787443572 18
1787443577 18
1787443582 18
1787443587 18
1787443592 18
1787443597 18
1787443602 16
1787443607 16
1787443612 16
1787443617 16
1787443622 16
1787443627 16
1787443632 16
1787443637 16
1787443642 18
1787443647 18
1787443652 18
1787443657 18
1787443662 18
```
</details>

---

