---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-29 00:58:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1787979232 59
1787979237 59
1787979242 59
1787979247 59
1787979252 59
1787979257 59
1787979262 59
1787979267 59
1787979272 59
1787979277 59
1787979282 59
1787979287 59
1787979292 61
1787979297 61
1787979302 59
1787979307 59
1787979312 59
1787979317 59
1787979322 57
1787979327 57
```
</details>

---

