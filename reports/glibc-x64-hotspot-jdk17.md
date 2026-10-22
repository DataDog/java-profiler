---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 13:06:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792688444 32
1792688449 32
1792688454 32
1792688459 32
1792688464 32
1792688469 32
1792688474 32
1792688479 32
1792688484 32
1792688489 32
1792688494 32
1792688499 32
1792688504 32
1792688509 32
1792688514 32
1792688519 30
1792688524 30
1792688529 30
1792688534 30
1792688539 30
```
</details>

---

