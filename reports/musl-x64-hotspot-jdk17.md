---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-30 10:04:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (5 unique values: 77-86 cores)</summary>

```
1777557239 77
1777557244 77
1777557249 77
1777557254 77
1777557259 78
1777557264 78
1777557269 78
1777557274 78
1777557279 78
1777557284 78
1777557289 78
1777557294 78
1777557299 78
1777557304 82
1777557309 82
1777557314 82
1777557319 84
1777557324 84
1777557329 84
1777557334 84
```
</details>

---

