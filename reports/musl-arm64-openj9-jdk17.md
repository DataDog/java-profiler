---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:01:31 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794585401 48
1794585406 48
1794585411 48
1794585416 48
1794585421 48
1794585426 48
1794585431 48
1794585436 48
1794585441 48
1794585446 48
1794585451 48
1794585456 48
1794585461 48
1794585466 48
1794585471 43
1794585476 43
1794585481 43
1794585486 43
1794585491 43
1794585497 43
```
</details>

---

