---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:09:24 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1794506730 19
1794506735 19
1794506740 19
1794506745 24
1794506750 24
1794506755 24
1794506760 24
1794506765 24
1794506770 24
1794506775 24
1794506780 24
1794506785 24
1794506790 24
1794506795 24
1794506800 24
1794506805 24
1794506810 24
1794506815 24
1794506820 24
1794506825 24
```
</details>

---

