---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 06:26:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 34-48 cores)</summary>

```
1789640491 38
1789640496 38
1789640501 43
1789640506 43
1789640511 43
1789640516 43
1789640521 43
1789640526 43
1789640531 48
1789640536 48
1789640541 48
1789640546 48
1789640551 48
1789640556 48
1789640561 48
1789640566 48
1789640571 48
1789640576 48
1789640581 39
1789640586 39
```
</details>

---

