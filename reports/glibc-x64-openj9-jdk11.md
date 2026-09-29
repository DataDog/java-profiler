---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 10:43:23 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1121 |
| Sample Rate | 18.68/sec |
| Health Score | 1168% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 57-61 cores)</summary>

```
1790692621 57
1790692626 57
1790692631 57
1790692636 57
1790692641 57
1790692646 57
1790692651 57
1790692656 57
1790692661 57
1790692666 57
1790692671 57
1790692676 57
1790692681 57
1790692686 57
1790692691 57
1790692696 57
1790692701 61
1790692706 61
1790692711 61
1790692716 61
```
</details>

---

