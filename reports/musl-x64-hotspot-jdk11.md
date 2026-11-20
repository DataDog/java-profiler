---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 09:57:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (5 unique values: 80-89 cores)</summary>

```
1795186241 80
1795186246 80
1795186251 80
1795186256 80
1795186261 82
1795186266 82
1795186271 82
1795186276 82
1795186281 82
1795186286 82
1795186291 82
1795186296 82
1795186301 82
1795186306 85
1795186311 85
1795186316 85
1795186321 85
1795186326 85
1795186331 85
1795186336 87
```
</details>

---

