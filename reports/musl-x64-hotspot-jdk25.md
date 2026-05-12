---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 08:29:47 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1037 |
| Sample Rate | 17.28/sec |
| Health Score | 1080% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 52-57 cores)</summary>

```
1778588569 52
1778588574 52
1778588579 52
1778588584 52
1778588589 52
1778588594 52
1778588599 52
1778588604 57
1778588609 57
1778588614 57
1778588619 57
1778588624 57
1778588629 57
1778588634 57
1778588639 57
1778588644 57
1778588649 57
1778588654 57
1778588659 57
1778588664 57
```
</details>

---

