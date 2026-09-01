---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-01 14:36:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 16 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
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
1788287433 64
1788287438 64
1788287443 64
1788287448 64
1788287453 64
1788287458 64
1788287463 64
1788287468 64
1788287473 64
```
</details>

---

