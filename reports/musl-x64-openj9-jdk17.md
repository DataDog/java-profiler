---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 09:32:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 11 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (3 unique values: 60-88 cores)</summary>

```
1787232400 88
1787232405 88
1787232410 88
1787232415 88
1787232420 88
1787232425 68
1787232430 68
1787232435 68
1787232440 68
1787232445 68
1787232450 68
1787232455 68
1787232460 68
1787232465 68
1787232470 68
1787232475 68
1787232480 60
1787232485 60
1787232490 60
1787232495 60
```
</details>

---

