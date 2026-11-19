---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 11:31:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 969 |
| Sample Rate | 16.15/sec |
| Health Score | 1009% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795105612 50
1795105617 50
1795105622 50
1795105627 50
1795105632 50
1795105637 50
1795105642 50
1795105647 50
1795105652 50
1795105657 50
1795105662 50
1795105667 50
1795105673 50
1795105678 50
1795105683 50
1795105688 50
1795105693 50
1795105698 50
1795105703 50
1795105708 50
```
</details>

---

