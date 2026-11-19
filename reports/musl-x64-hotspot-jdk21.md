---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:15:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 951 |
| Sample Rate | 15.85/sec |
| Health Score | 991% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 36-46 cores)</summary>

```
1795108232 36
1795108237 36
1795108242 36
1795108247 36
1795108252 36
1795108257 46
1795108262 46
1795108267 37
1795108272 37
1795108277 37
1795108282 37
1795108287 37
1795108292 37
1795108297 37
1795108302 37
1795108307 37
1795108312 37
1795108317 37
1795108322 37
1795108327 37
```
</details>

---

