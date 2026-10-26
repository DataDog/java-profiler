---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-25 21:27:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 59-94 cores)</summary>

```
1792977710 61
1792977715 61
1792977720 61
1792977725 61
1792977730 61
1792977735 61
1792977740 61
1792977745 61
1792977750 61
1792977755 59
1792977760 59
1792977765 59
1792977770 59
1792977775 59
1792977780 59
1792977785 63
1792977790 63
1792977795 61
1792977800 61
1792977805 61
```
</details>

---

