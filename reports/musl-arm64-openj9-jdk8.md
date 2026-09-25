---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-25 10:31:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1790346390 50
1790346395 50
1790346400 50
1790346405 50
1790346410 50
1790346415 50
1790346420 50
1790346425 50
1790346430 50
1790346436 50
1790346441 50
1790346446 50
1790346451 45
1790346456 45
1790346461 45
1790346466 45
1790346471 45
1790346476 45
1790346481 45
1790346486 45
```
</details>

---

