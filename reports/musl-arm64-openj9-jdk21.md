---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-21 09:26:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1787318479 45
1787318484 45
1787318489 45
1787318494 48
1787318499 48
1787318504 48
1787318509 48
1787318514 48
1787318519 48
1787318524 48
1787318529 48
1787318534 48
1787318539 48
1787318544 48
1787318549 48
1787318554 48
1787318559 48
1787318564 48
1787318569 48
1787318574 47
```
</details>

---

