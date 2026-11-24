---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 08:09:18 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 12 |
| Allocations | 164 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795525448 64
1795525453 64
1795525458 64
1795525463 64
1795525468 64
1795525473 64
1795525478 64
1795525483 64
1795525488 64
1795525493 64
1795525498 64
1795525503 64
1795525508 64
1795525513 64
1795525518 64
1795525524 64
1795525529 64
1795525534 64
1795525539 64
1795525544 64
```
</details>

---

