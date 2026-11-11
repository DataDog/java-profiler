---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 04:53:58 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794390425 47
1794390430 47
1794390435 47
1794390440 47
1794390445 48
1794390450 48
1794390455 48
1794390460 48
1794390465 48
1794390470 48
1794390475 48
1794390480 48
1794390485 48
1794390490 48
1794390495 48
1794390500 48
1794390505 48
1794390510 48
1794390515 48
1794390520 48
```
</details>

---

