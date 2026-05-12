---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 08:29:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (5 unique values: 33-62 cores)</summary>

```
1778588564 62
1778588569 58
1778588574 58
1778588579 58
1778588584 58
1778588589 58
1778588594 58
1778588599 58
1778588604 58
1778588609 58
1778588614 58
1778588619 58
1778588624 58
1778588629 43
1778588634 43
1778588639 33
1778588644 33
1778588649 33
1778588654 33
1778588659 33
```
</details>

---

