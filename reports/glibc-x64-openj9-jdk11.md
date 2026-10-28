---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:39:34 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 872 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1793205330 76
1793205335 76
1793205340 76
1793205345 76
1793205350 76
1793205355 76
1793205360 74
1793205365 74
1793205370 74
1793205375 74
1793205380 74
1793205386 74
1793205391 74
1793205396 74
1793205401 74
1793205406 74
1793205411 74
1793205416 74
1793205421 74
1793205426 74
```
</details>

---

