---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-27 21:23:50 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 34-64 cores)</summary>

```
1790558383 34
1790558388 34
1790558393 34
1790558398 34
1790558403 34
1790558408 34
1790558413 34
1790558418 34
1790558423 34
1790558428 34
1790558433 34
1790558438 34
1790558443 34
1790558448 34
1790558453 34
1790558458 34
1790558463 64
1790558468 64
1790558473 64
1790558478 64
```
</details>

---

