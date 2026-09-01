---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-01 14:36:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 11 |
| Allocations | 165 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1788287333 47
1788287338 47
1788287343 47
1788287348 47
1788287353 47
1788287358 47
1788287363 47
1788287368 47
1788287373 47
1788287378 47
1788287383 47
1788287388 47
1788287393 47
1788287398 47
1788287403 47
1788287408 47
1788287413 47
1788287418 47
1788287423 64
1788287428 64
```
</details>

---

