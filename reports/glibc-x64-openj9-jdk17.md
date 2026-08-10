---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 09:14:01 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 11 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (3 unique values: 71-76 cores)</summary>

```
1786367378 71
1786367383 71
1786367388 71
1786367393 71
1786367398 71
1786367403 76
1786367408 76
1786367413 76
1786367418 76
1786367423 76
1786367428 76
1786367433 74
1786367438 74
1786367443 74
1786367448 74
1786367453 74
1786367458 74
1786367463 74
1786367468 74
1786367473 74
```
</details>

---

