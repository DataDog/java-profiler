---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:03:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 11 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 82-96 cores)</summary>

```
1789743419 82
1789743424 82
1789743429 82
1789743434 82
1789743439 82
1789743444 82
1789743449 82
1789743454 82
1789743459 82
1789743464 84
1789743469 84
1789743474 84
1789743479 84
1789743484 96
1789743489 96
1789743494 96
1789743499 96
1789743504 96
1789743509 96
1789743514 96
```
</details>

---

