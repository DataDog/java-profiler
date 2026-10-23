---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 10:04:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 55-78 cores)</summary>

```
1792764021 78
1792764026 78
1792764031 78
1792764036 78
1792764041 78
1792764046 58
1792764051 58
1792764056 58
1792764061 58
1792764066 58
1792764071 58
1792764076 58
1792764081 58
1792764086 58
1792764091 58
1792764096 58
1792764101 76
1792764106 76
1792764111 55
1792764116 55
```
</details>

---

