---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-24 18:13:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787609399 32
1787609404 32
1787609409 32
1787609414 32
1787609419 32
1787609424 32
1787609429 32
1787609434 32
1787609439 32
1787609444 32
1787609449 32
1787609454 32
1787609459 32
1787609464 32
1787609469 32
1787609474 32
1787609479 32
1787609484 32
1787609489 32
1787609494 32
```
</details>

---

