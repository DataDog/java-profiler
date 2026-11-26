---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 00:04:45 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795669249 62
1795669254 64
1795669259 64
1795669264 64
1795669269 64
1795669274 64
1795669279 64
1795669284 64
1795669289 64
1795669294 64
1795669299 64
1795669304 64
1795669309 64
1795669314 64
1795669319 64
1795669324 64
1795669329 64
1795669334 64
1795669339 64
1795669344 64
```
</details>

---

