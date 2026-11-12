---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:08:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 5 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1794506559 10
1794506564 10
1794506569 10
1794506574 10
1794506579 12
1794506584 12
1794506589 12
1794506594 12
1794506599 12
1794506604 12
1794506609 12
1794506614 12
1794506619 12
1794506624 12
1794506629 12
1794506634 12
1794506639 12
1794506644 12
1794506649 12
1794506654 12
```
</details>

---

