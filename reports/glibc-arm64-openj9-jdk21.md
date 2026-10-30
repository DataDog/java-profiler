---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 01:04:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793336454 48
1793336459 48
1793336464 48
1793336469 48
1793336474 48
1793336479 48
1793336484 48
1793336489 48
1793336494 48
1793336499 48
1793336504 48
1793336509 48
1793336514 48
1793336519 48
1793336524 48
1793336529 48
1793336534 48
1793336539 43
1793336544 43
1793336549 43
```
</details>

---

