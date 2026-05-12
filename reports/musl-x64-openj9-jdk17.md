---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 09:20:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 932 |
| Sample Rate | 15.53/sec |
| Health Score | 971% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 53-65 cores)</summary>

```
1778591654 57
1778591659 57
1778591664 57
1778591669 57
1778591674 57
1778591679 57
1778591684 57
1778591689 57
1778591694 53
1778591699 53
1778591704 53
1778591709 53
1778591714 53
1778591719 53
1778591724 55
1778591729 55
1778591734 55
1778591739 55
1778591744 53
1778591749 53
```
</details>

---

