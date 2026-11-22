---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 05:47:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1795344251 36
1795344256 36
1795344261 36
1795344266 36
1795344271 36
1795344276 36
1795344281 36
1795344286 36
1795344291 36
1795344296 36
1795344301 36
1795344306 36
1795344312 36
1795344317 36
1795344322 36
1795344327 36
1795344332 36
1795344337 36
1795344342 34
1795344347 34
```
</details>

---

