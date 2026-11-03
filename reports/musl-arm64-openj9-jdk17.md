---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 21:59:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 14 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1793674469 34
1793674474 34
1793674479 34
1793674484 34
1793674489 34
1793674494 34
1793674499 34
1793674504 34
1793674509 34
1793674514 34
1793674519 34
1793674524 39
1793674529 39
1793674534 34
1793674539 34
1793674544 34
1793674549 34
1793674554 34
1793674559 34
1793674564 34
```
</details>

---

