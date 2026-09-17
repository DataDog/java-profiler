---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:57:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 60-70 cores)</summary>

```
1789677737 70
1789677742 70
1789677747 60
1789677753 60
1789677758 60
1789677763 60
1789677768 60
1789677773 60
1789677778 60
1789677783 60
1789677788 60
1789677793 60
1789677798 60
1789677803 60
1789677808 60
1789677813 60
1789677818 60
1789677823 60
1789677828 61
1789677833 61
```
</details>

---

