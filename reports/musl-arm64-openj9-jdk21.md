---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 04:18:24 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1786522380 48
1786522385 43
1786522390 43
1786522395 43
1786522400 43
1786522405 43
1786522410 43
1786522415 43
1786522420 43
1786522425 43
1786522430 43
1786522435 42
1786522440 42
1786522445 42
1786522450 42
1786522455 42
1786522460 42
1786522465 42
1786522470 42
1786522475 42
```
</details>

---

