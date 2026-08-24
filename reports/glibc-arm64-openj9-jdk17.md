---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-24 18:13:26 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 13 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787609411 32
1787609416 32
1787609421 32
1787609426 32
1787609431 32
1787609436 32
1787609441 32
1787609446 32
1787609451 32
1787609456 32
1787609461 32
1787609466 32
1787609471 32
1787609476 32
1787609481 32
1787609486 32
1787609491 32
1787609496 32
1787609501 32
1787609506 32
```
</details>

---

