---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-17 01:02:28 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1786942374 26
1786942379 26
1786942384 26
1786942389 26
1786942394 26
1786942399 28
1786942404 28
1786942409 28
1786942414 28
1786942419 28
1786942424 28
1786942429 28
1786942434 28
1786942439 28
1786942444 28
1786942449 28
1786942454 28
1786942459 28
1786942464 28
1786942469 28
```
</details>

---

