---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:05:34 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1789743439 45
1789743444 45
1789743449 45
1789743454 45
1789743459 45
1789743464 45
1789743469 48
1789743474 48
1789743479 48
1789743484 48
1789743489 48
1789743494 48
1789743499 48
1789743504 48
1789743509 48
1789743514 48
1789743519 48
1789743524 48
1789743529 48
1789743534 48
```
</details>

---

