---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 00:57:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 68-96 cores)</summary>

```
1789966364 96
1789966369 96
1789966374 96
1789966379 68
1789966384 68
1789966389 68
1789966394 68
1789966399 68
1789966404 68
1789966409 68
1789966414 68
1789966419 68
1789966424 68
1789966429 68
1789966434 68
1789966439 68
1789966444 68
1789966449 68
1789966454 68
1789966459 68
```
</details>

---

