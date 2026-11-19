---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:16:28 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 53-65 cores)</summary>

```
1795108247 53
1795108252 53
1795108257 53
1795108262 53
1795108267 53
1795108272 55
1795108277 55
1795108282 55
1795108287 55
1795108292 63
1795108297 63
1795108302 63
1795108307 63
1795108312 63
1795108317 63
1795108322 63
1795108327 63
1795108332 63
1795108337 63
1795108342 63
```
</details>

---

