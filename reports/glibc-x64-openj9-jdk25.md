---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 05:15:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (5 unique values: 68-87 cores)</summary>

```
1777281133 68
1777281138 68
1777281143 68
1777281148 71
1777281153 71
1777281158 76
1777281163 76
1777281168 76
1777281173 76
1777281178 76
1777281183 82
1777281188 82
1777281193 82
1777281198 82
1777281203 82
1777281208 87
1777281213 87
1777281218 87
1777281223 87
1777281228 87
```
</details>

---

