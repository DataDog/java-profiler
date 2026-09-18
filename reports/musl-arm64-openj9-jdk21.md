---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:15:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (7 unique values: 29-59 cores)</summary>

```
1789743616 29
1789743621 34
1789743626 34
1789743631 39
1789743636 39
1789743641 39
1789743646 43
1789743651 43
1789743656 53
1789743661 53
1789743666 53
1789743671 53
1789743676 58
1789743681 58
1789743686 58
1789743691 58
1789743696 59
1789743701 59
1789743706 59
1789743711 59
```
</details>

---

