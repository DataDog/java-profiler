---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 09:00:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 10 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778158383 64
1778158388 64
1778158393 64
1778158398 64
1778158403 64
1778158408 64
1778158413 64
1778158418 64
1778158423 64
1778158428 64
1778158433 64
1778158438 64
1778158443 64
1778158448 64
1778158453 64
1778158458 64
1778158463 64
1778158468 64
1778158473 64
1778158478 64
```
</details>

---

