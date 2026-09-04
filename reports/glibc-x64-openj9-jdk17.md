---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-04 05:50:50 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1788515224 90
1788515229 90
1788515234 92
1788515239 92
1788515244 92
1788515249 92
1788515254 92
1788515259 96
1788515264 96
1788515269 96
1788515274 96
1788515279 96
1788515284 96
1788515289 96
1788515294 96
1788515299 96
1788515304 96
1788515309 96
1788515314 96
1788515319 96
```
</details>

---

