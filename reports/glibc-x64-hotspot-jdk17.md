---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 11:54:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 55-79 cores)</summary>

```
1795798236 72
1795798241 72
1795798246 72
1795798251 72
1795798256 55
1795798261 55
1795798266 55
1795798271 55
1795798276 55
1795798281 55
1795798286 55
1795798291 55
1795798296 55
1795798301 55
1795798306 55
1795798311 55
1795798316 55
1795798321 55
1795798326 55
1795798331 55
```
</details>

---

