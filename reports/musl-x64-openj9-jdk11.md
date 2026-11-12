---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:08:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 53-74 cores)</summary>

```
1794506539 71
1794506544 71
1794506549 71
1794506554 71
1794506559 71
1794506564 71
1794506569 71
1794506574 71
1794506579 71
1794506584 71
1794506589 71
1794506594 71
1794506599 71
1794506604 71
1794506609 71
1794506614 74
1794506619 74
1794506624 74
1794506629 74
1794506634 53
```
</details>

---

