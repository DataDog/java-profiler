---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 16:31:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 12 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 70-94 cores)</summary>

```
1786393622 70
1786393627 70
1786393632 70
1786393637 94
1786393642 94
1786393647 94
1786393652 94
1786393657 94
1786393662 94
1786393667 94
1786393672 94
1786393677 92
1786393682 92
1786393687 92
1786393692 92
1786393697 92
1786393702 92
1786393707 92
1786393712 92
1786393717 92
```
</details>

---

