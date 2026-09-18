---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:11:55 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 7 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1789743476 46
1789743481 46
1789743486 46
1789743491 46
1789743496 46
1789743501 46
1789743506 46
1789743511 46
1789743516 46
1789743521 46
1789743526 46
1789743531 46
1789743536 46
1789743541 46
1789743546 46
1789743551 46
1789743556 64
1789743561 64
1789743566 64
1789743571 64
```
</details>

---

