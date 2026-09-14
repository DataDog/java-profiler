---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-14 12:04:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (5 unique values: 88-96 cores)</summary>

```
1789401576 88
1789401581 88
1789401586 90
1789401591 90
1789401596 90
1789401601 92
1789401606 92
1789401611 92
1789401616 92
1789401621 96
1789401626 96
1789401631 96
1789401636 96
1789401641 96
1789401646 96
1789401651 96
1789401656 94
1789401661 94
1789401666 94
1789401671 94
```
</details>

---

