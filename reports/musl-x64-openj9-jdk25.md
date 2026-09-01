---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-01 14:36:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788287333 62
1788287338 62
1788287343 62
1788287348 62
1788287353 62
1788287358 62
1788287363 64
1788287368 64
1788287373 64
1788287378 64
1788287383 64
1788287388 64
1788287393 64
1788287398 64
1788287403 64
1788287408 64
1788287413 64
1788287418 64
1788287423 64
1788287428 64
```
</details>

---

