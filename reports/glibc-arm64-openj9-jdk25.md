---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 20:29:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 9 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 14 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795397206 34
1795397211 34
1795397216 34
1795397221 34
1795397226 34
1795397231 34
1795397236 34
1795397241 34
1795397246 34
1795397251 34
1795397256 34
1795397261 34
1795397266 34
1795397271 34
1795397276 34
1795397281 34
1795397286 34
1795397291 29
1795397296 29
1795397301 29
```
</details>

---

