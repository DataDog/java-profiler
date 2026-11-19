---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 11:31:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 10 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795105659 50
1795105664 50
1795105669 50
1795105674 50
1795105679 50
1795105684 50
1795105689 50
1795105694 50
1795105699 50
1795105704 50
1795105709 50
1795105714 50
1795105719 50
1795105724 50
1795105729 50
1795105734 50
1795105739 50
1795105744 50
1795105749 50
1795105754 50
```
</details>

---

