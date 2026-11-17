---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 10:02:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 932 |
| Sample Rate | 15.53/sec |
| Health Score | 971% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794927394 41
1794927399 41
1794927404 41
1794927409 41
1794927414 46
1794927419 46
1794927424 46
1794927429 46
1794927434 46
1794927439 46
1794927444 46
1794927450 46
1794927455 46
1794927460 46
1794927465 46
1794927470 46
1794927475 46
1794927480 46
1794927485 46
1794927490 46
```
</details>

---

