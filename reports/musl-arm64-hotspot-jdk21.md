---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 04:18:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1786522370 48
1786522375 48
1786522380 43
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
```
</details>

---

