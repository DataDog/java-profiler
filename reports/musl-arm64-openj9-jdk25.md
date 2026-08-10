---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 09:32:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (4 unique values: 24-30 cores)</summary>

```
1786368420 24
1786368425 24
1786368430 24
1786368435 24
1786368440 24
1786368445 29
1786368450 29
1786368455 29
1786368460 29
1786368465 29
1786368470 29
1786368475 30
1786368480 30
1786368485 27
1786368490 27
1786368495 27
1786368500 27
1786368505 27
1786368510 27
1786368515 27
```
</details>

---

