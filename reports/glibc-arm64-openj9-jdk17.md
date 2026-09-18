---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:10:34 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789743434 38
1789743439 43
1789743444 43
1789743449 43
1789743454 43
1789743459 43
1789743464 43
1789743469 43
1789743474 43
1789743479 43
1789743484 43
1789743489 43
1789743494 43
1789743499 43
1789743504 43
1789743509 43
1789743514 43
1789743519 43
1789743524 43
1789743529 43
```
</details>

---

