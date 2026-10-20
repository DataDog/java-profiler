---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 07:43:41 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 12 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792496332 43
1792496337 43
1792496342 43
1792496347 43
1792496352 43
1792496357 43
1792496362 43
1792496367 43
1792496372 43
1792496377 43
1792496382 43
1792496387 43
1792496392 48
1792496397 48
1792496402 48
1792496407 48
1792496412 48
1792496418 48
1792496423 48
1792496428 48
```
</details>

---

