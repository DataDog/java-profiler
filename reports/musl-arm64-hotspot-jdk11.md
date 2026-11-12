---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:21:25 EST

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
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1794507380 48
1794507385 48
1794507390 48
1794507395 48
1794507400 48
1794507405 48
1794507410 48
1794507415 48
1794507420 48
1794507425 48
1794507430 48
1794507435 48
1794507440 48
1794507445 48
1794507450 48
1794507455 48
1794507460 48
1794507465 48
1794507470 48
1794507475 48
```
</details>

---

