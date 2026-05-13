---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-13 09:58:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 53-59 cores)</summary>

```
1778680377 59
1778680382 59
1778680387 59
1778680392 59
1778680397 59
1778680402 59
1778680407 59
1778680412 59
1778680417 59
1778680423 59
1778680428 59
1778680433 59
1778680438 59
1778680443 59
1778680448 59
1778680453 59
1778680458 59
1778680463 53
1778680468 53
1778680473 53
```
</details>

---

