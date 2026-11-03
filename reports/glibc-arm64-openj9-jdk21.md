---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 21:59:30 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 34-51 cores)</summary>

```
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
1793674569 34
1793674574 34
1793674579 34
1793674584 34
1793674589 34
1793674594 34
```
</details>

---

