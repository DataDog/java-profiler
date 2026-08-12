---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 04:18:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 201 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 9 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 18-30 cores)</summary>

```
1786522385 30
1786522390 30
1786522395 30
1786522400 30
1786522405 30
1786522410 30
1786522415 30
1786522420 25
1786522425 25
1786522430 25
1786522435 25
1786522440 25
1786522445 25
1786522450 25
1786522455 25
1786522460 25
1786522465 25
1786522470 30
1786522475 30
1786522480 30
```
</details>

---

