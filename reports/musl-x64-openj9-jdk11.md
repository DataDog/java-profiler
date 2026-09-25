---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 09:23:20 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 9 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (4 unique values: 52-87 cores)</summary>

```
1790342278 52
1790342283 52
1790342288 62
1790342293 62
1790342298 87
1790342303 87
1790342308 87
1790342313 87
1790342318 87
1790342323 55
1790342328 55
1790342333 55
1790342338 55
1790342343 55
1790342348 55
1790342353 55
1790342358 55
1790342363 55
1790342368 55
1790342373 55
```
</details>

---

