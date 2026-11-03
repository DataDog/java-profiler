---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 21:59:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 59-96 cores)</summary>

```
1793674445 94
1793674450 96
1793674455 96
1793674460 96
1793674465 96
1793674470 96
1793674475 96
1793674480 96
1793674485 96
1793674490 94
1793674495 94
1793674500 92
1793674505 92
1793674510 92
1793674515 92
1793674520 92
1793674525 92
1793674530 92
1793674535 92
1793674540 92
```
</details>

---

