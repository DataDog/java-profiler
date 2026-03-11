---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 10:47:08 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 940 |
| Sample Rate | 15.67/sec |
| Health Score | 979% |
| Threads | 12 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 68-72 cores)</summary>

```
1773240127 70
1773240132 70
1773240137 70
1773240142 72
1773240147 72
1773240152 68
1773240157 68
1773240163 70
1773240168 70
1773240173 70
1773240178 70
1773240183 70
1773240188 70
1773240193 70
1773240198 70
1773240203 70
1773240208 68
1773240213 68
1773240218 68
1773240223 70
```
</details>

---

