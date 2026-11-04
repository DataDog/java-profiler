---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 15:01:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 10 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1793822208 30
1793822213 30
1793822218 28
1793822223 28
1793822228 28
1793822233 28
1793822238 28
1793822243 28
1793822248 30
1793822253 30
1793822258 30
1793822263 32
1793822268 32
1793822273 32
1793822278 32
1793822283 32
1793822288 32
1793822293 32
1793822298 32
1793822303 32
```
</details>

---

