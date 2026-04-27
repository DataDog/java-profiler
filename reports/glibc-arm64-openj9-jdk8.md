---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-27 14:34:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777314561 64
1777314566 64
1777314571 64
1777314576 64
1777314581 64
1777314586 64
1777314591 64
1777314596 64
1777314601 64
1777314606 64
1777314611 64
1777314616 64
1777314621 64
1777314626 64
1777314631 64
1777314636 64
1777314641 64
1777314646 64
1777314651 64
1777314656 64
```
</details>

---

