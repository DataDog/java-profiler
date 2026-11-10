---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 14:09:21 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1794337449 29
1794337454 29
1794337459 29
1794337464 29
1794337469 29
1794337474 29
1794337479 29
1794337484 29
1794337489 29
1794337494 29
1794337499 29
1794337504 29
1794337509 29
1794337514 29
1794337519 32
1794337524 32
1794337529 32
1794337534 32
1794337539 27
1794337544 27
```
</details>

---

