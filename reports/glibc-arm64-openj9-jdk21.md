---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 16:17:03 EST

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
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 11 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 14 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1794604424 48
1794604429 43
1794604434 43
1794604439 43
1794604444 43
1794604449 43
1794604454 43
1794604459 43
1794604464 43
1794604469 41
1794604474 41
1794604479 41
1794604484 41
1794604489 41
1794604494 41
1794604499 41
1794604504 41
1794604509 41
1794604514 41
1794604519 41
```
</details>

---

