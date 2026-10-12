---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-12 03:21:24 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 17-34 cores)</summary>

```
1791789399 34
1791789404 34
1791789409 34
1791789414 34
1791789419 34
1791789424 22
1791789429 22
1791789434 22
1791789439 22
1791789444 22
1791789449 22
1791789454 22
1791789459 22
1791789464 22
1791789469 22
1791789474 22
1791789479 22
1791789484 17
1791789489 17
1791789494 17
```
</details>

---

