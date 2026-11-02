---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 10:00:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793631377 48
1793631382 48
1793631387 48
1793631392 48
1793631397 48
1793631402 48
1793631407 48
1793631412 48
1793631417 48
1793631422 48
1793631427 48
1793631432 48
1793631437 48
1793631442 48
1793631447 48
1793631452 48
1793631457 48
1793631462 43
1793631467 43
1793631472 43
```
</details>

---

