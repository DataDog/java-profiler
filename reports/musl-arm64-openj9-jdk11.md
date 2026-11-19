---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:15:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 7 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 14 |
| Allocations | 165 |

<details>
<summary>CPU Timeline (2 unique values: 46-50 cores)</summary>

```
1795108232 50
1795108237 50
1795108242 50
1795108247 50
1795108252 50
1795108257 50
1795108262 50
1795108267 50
1795108272 50
1795108277 50
1795108282 50
1795108287 50
1795108292 50
1795108297 50
1795108302 46
1795108307 46
1795108312 46
1795108317 46
1795108322 46
1795108327 46
```
</details>

---

