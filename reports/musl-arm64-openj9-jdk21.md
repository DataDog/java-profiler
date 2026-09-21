---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 05:26:31 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 12 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1789982386 43
1789982391 43
1789982396 43
1789982401 43
1789982406 43
1789982411 43
1789982416 43
1789982421 43
1789982426 43
1789982431 38
1789982436 38
1789982441 38
1789982446 38
1789982451 38
1789982456 38
1789982461 38
1789982466 38
1789982471 38
1789982476 38
1789982481 43
```
</details>

---

