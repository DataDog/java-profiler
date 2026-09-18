---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:07:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (5 unique values: 39-49 cores)</summary>

```
1789743506 45
1789743511 45
1789743516 45
1789743521 45
1789743526 45
1789743531 43
1789743537 43
1789743542 43
1789743547 43
1789743552 41
1789743557 41
1789743562 41
1789743567 39
1789743572 39
1789743577 39
1789743582 39
1789743587 43
1789743592 43
1789743597 45
1789743602 45
```
</details>

---

