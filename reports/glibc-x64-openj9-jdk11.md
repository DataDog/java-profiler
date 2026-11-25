---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 08:34:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1795613395 85
1795613400 85
1795613405 85
1795613410 85
1795613415 85
1795613420 85
1795613425 85
1795613430 85
1795613435 85
1795613440 85
1795613445 85
1795613450 85
1795613455 85
1795613460 85
1795613465 85
1795613470 85
1795613475 94
1795613480 94
1795613485 94
1795613490 94
```
</details>

---

