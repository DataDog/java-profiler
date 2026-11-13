---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 14:19:35 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794597344 32
1794597349 32
1794597354 32
1794597359 32
1794597364 32
1794597369 32
1794597374 32
1794597379 32
1794597384 32
1794597389 32
1794597394 32
1794597399 32
1794597404 32
1794597409 32
1794597414 32
1794597419 32
1794597424 32
1794597429 32
1794597434 32
1794597439 32
```
</details>

---

