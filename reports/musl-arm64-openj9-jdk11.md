---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-30 05:41:43 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769769464 24
1769769469 24
1769769474 24
1769769479 24
1769769484 24
1769769489 24
1769769494 24
1769769499 24
1769769504 24
1769769509 24
1769769514 24
1769769519 24
1769769524 24
1769769529 24
1769769534 24
1769769539 24
1769769544 24
1769769549 24
1769769554 24
1769769559 24
```
</details>

---

