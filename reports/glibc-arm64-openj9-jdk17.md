---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 00:57:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 24-29 cores)</summary>

```
1789966367 24
1789966372 24
1789966377 24
1789966382 24
1789966387 24
1789966392 24
1789966397 24
1789966402 24
1789966407 24
1789966412 24
1789966417 29
1789966422 29
1789966427 26
1789966432 26
1789966437 26
1789966442 26
1789966447 26
1789966452 26
1789966457 26
1789966462 26
```
</details>

---

