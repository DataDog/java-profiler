---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 11:31:14 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 14.87/sec |
| Health Score | 929% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 59-83 cores)</summary>

```
1795105587 61
1795105592 61
1795105597 61
1795105602 61
1795105607 61
1795105612 61
1795105617 61
1795105622 61
1795105627 61
1795105632 61
1795105637 61
1795105642 61
1795105647 61
1795105652 61
1795105657 61
1795105662 59
1795105667 59
1795105672 59
1795105677 59
1795105682 59
```
</details>

---

