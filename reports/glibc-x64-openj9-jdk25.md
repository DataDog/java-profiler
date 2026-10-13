---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 12:35:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1791908970 45
1791908975 45
1791908980 45
1791908985 45
1791908990 45
1791908995 45
1791909000 45
1791909005 45
1791909010 45
1791909015 45
1791909020 45
1791909025 45
1791909030 43
1791909035 43
1791909040 43
1791909045 43
1791909050 43
1791909055 43
1791909060 43
1791909065 43
```
</details>

---

