---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-16 10:46:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (5 unique values: 72-85 cores)</summary>

```
1792161440 74
1792161445 72
1792161450 72
1792161455 72
1792161460 72
1792161465 72
1792161470 75
1792161475 75
1792161480 75
1792161485 77
1792161490 77
1792161495 77
1792161500 77
1792161505 77
1792161510 77
1792161515 77
1792161520 85
1792161525 85
1792161530 85
1792161535 85
```
</details>

---

