---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 09:00:15 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 9 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (4 unique values: 50-60 cores)</summary>

```
1778158369 54
1778158374 54
1778158379 54
1778158384 54
1778158389 54
1778158394 54
1778158399 54
1778158404 54
1778158409 50
1778158414 50
1778158419 55
1778158424 55
1778158429 55
1778158434 55
1778158439 55
1778158444 55
1778158449 55
1778158454 55
1778158459 60
1778158464 60
```
</details>

---

