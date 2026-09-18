---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:03:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 13 |
| Allocations | 199 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789743476 48
1789743481 48
1789743486 48
1789743491 48
1789743496 48
1789743501 48
1789743506 48
1789743511 48
1789743516 48
1789743521 48
1789743526 48
1789743531 48
1789743536 43
1789743541 43
1789743546 43
1789743551 43
1789743556 43
1789743561 43
1789743566 43
1789743571 43
```
</details>

---

