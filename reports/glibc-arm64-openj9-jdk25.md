---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:33:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 15-25 cores)</summary>

```
1789716446 15
1789716451 15
1789716456 15
1789716461 15
1789716466 15
1789716471 15
1789716476 15
1789716481 15
1789716486 15
1789716491 15
1789716496 15
1789716501 15
1789716506 15
1789716511 15
1789716516 15
1789716521 15
1789716526 15
1789716531 15
1789716536 20
1789716541 20
```
</details>

---

