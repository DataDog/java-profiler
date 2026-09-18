---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:03:10 EDT

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
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 32-42 cores)</summary>

```
1789743461 32
1789743466 32
1789743471 32
1789743476 32
1789743481 37
1789743486 37
1789743491 37
1789743496 37
1789743501 37
1789743506 37
1789743511 37
1789743516 37
1789743521 37
1789743526 37
1789743531 37
1789743536 37
1789743541 37
1789743546 37
1789743551 37
1789743556 37
```
</details>

---

