---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:07:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 72-80 cores)</summary>

```
1793372584 80
1793372589 80
1793372594 80
1793372599 80
1793372604 80
1793372610 80
1793372615 80
1793372620 80
1793372625 80
1793372630 80
1793372635 80
1793372640 80
1793372645 80
1793372650 80
1793372655 80
1793372660 80
1793372665 80
1793372670 80
1793372675 80
1793372680 80
```
</details>

---

