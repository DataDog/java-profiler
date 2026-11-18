---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:31:19 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 52-73 cores)</summary>

```
1795008246 52
1795008251 52
1795008256 52
1795008261 52
1795008266 52
1795008271 52
1795008276 73
1795008281 73
1795008286 73
1795008291 72
1795008296 72
1795008301 72
1795008306 72
1795008311 72
1795008316 72
1795008321 72
1795008326 72
1795008331 72
1795008336 72
1795008341 72
```
</details>

---

