---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:40:11 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 872 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 73-82 cores)</summary>

```
1795192438 75
1795192443 75
1795192448 75
1795192453 75
1795192458 75
1795192463 75
1795192468 75
1795192473 75
1795192478 75
1795192483 75
1795192488 75
1795192493 73
1795192498 73
1795192503 73
1795192508 73
1795192513 73
1795192518 73
1795192523 82
1795192528 82
1795192533 82
```
</details>

---

