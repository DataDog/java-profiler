---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:39:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 9 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795451612 59
1795451617 59
1795451622 59
1795451627 59
1795451632 59
1795451637 59
1795451642 59
1795451647 59
1795451652 59
1795451657 64
1795451662 64
1795451667 64
1795451672 64
1795451677 64
1795451683 64
1795451688 64
1795451693 64
1795451698 64
1795451703 64
1795451708 64
```
</details>

---

