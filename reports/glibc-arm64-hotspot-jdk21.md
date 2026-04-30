---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 7 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 10 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1777557259 44
1777557264 44
1777557269 44
1777557274 44
1777557279 44
1777557284 48
1777557289 48
1777557294 48
1777557299 48
1777557304 43
1777557309 43
1777557314 43
1777557319 43
1777557324 48
1777557329 48
1777557334 48
1777557339 48
1777557344 48
1777557349 48
1777557354 48
```
</details>

---

