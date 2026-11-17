---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:02:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 38-51 cores)</summary>

```
1794927418 38
1794927423 38
1794927428 38
1794927433 38
1794927438 38
1794927443 46
1794927448 46
1794927453 51
1794927458 51
1794927463 51
1794927468 51
1794927473 51
1794927478 51
1794927483 51
1794927488 51
1794927493 51
1794927498 51
1794927503 51
1794927508 51
1794927513 51
```
</details>

---

