---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:36:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 60-74 cores)</summary>

```
1794569538 62
1794569543 62
1794569548 60
1794569553 60
1794569558 60
1794569563 67
1794569568 67
1794569573 67
1794569578 67
1794569583 67
1794569588 67
1794569593 67
1794569598 67
1794569603 67
1794569608 67
1794569613 67
1794569618 67
1794569623 67
1794569628 67
1794569633 67
```
</details>

---

