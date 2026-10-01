---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 11:00:42 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 10 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1790866541 47
1790866546 47
1790866551 45
1790866556 45
1790866561 45
1790866566 45
1790866571 45
1790866576 45
1790866581 45
1790866586 45
1790866591 45
1790866596 45
1790866601 45
1790866606 45
1790866611 45
1790866616 45
1790866621 45
1790866626 47
1790866631 47
1790866636 47
```
</details>

---

