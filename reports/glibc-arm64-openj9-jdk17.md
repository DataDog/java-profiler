---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 08:08:34 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1792670610 28
1792670615 28
1792670620 28
1792670625 28
1792670630 28
1792670635 28
1792670640 28
1792670645 28
1792670650 28
1792670655 28
1792670660 28
1792670665 28
1792670670 28
1792670675 48
1792670680 48
1792670685 48
1792670690 48
1792670695 48
1792670700 48
1792670705 48
```
</details>

---

