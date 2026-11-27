---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 11:54:57 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (4 unique values: 62-83 cores)</summary>

```
1795798241 73
1795798246 73
1795798251 71
1795798256 71
1795798261 71
1795798266 71
1795798271 71
1795798276 71
1795798281 71
1795798286 71
1795798291 71
1795798296 71
1795798301 62
1795798306 62
1795798311 62
1795798316 62
1795798321 62
1795798326 62
1795798331 62
1795798336 62
```
</details>

---

