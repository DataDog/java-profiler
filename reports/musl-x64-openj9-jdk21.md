---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-24 08:31:08 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 43-57 cores)</summary>

```
1777033622 43
1777033627 43
1777033632 43
1777033637 43
1777033642 43
1777033647 43
1777033652 43
1777033657 43
1777033662 43
1777033667 43
1777033672 43
1777033677 45
1777033682 45
1777033687 45
1777033692 45
1777033697 47
1777033702 47
1777033707 57
1777033712 57
1777033717 57
```
</details>

---

