---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-04 05:50:50 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 903 |
| Sample Rate | 15.05/sec |
| Health Score | 941% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1788515236 76
1788515242 76
1788515247 76
1788515252 76
1788515257 76
1788515262 76
1788515267 76
1788515272 76
1788515277 76
1788515282 76
1788515287 96
1788515292 96
1788515297 96
1788515302 96
1788515307 96
1788515312 96
1788515317 96
1788515322 96
1788515327 96
1788515332 96
```
</details>

---

