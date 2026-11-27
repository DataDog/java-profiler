---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 11:54:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795798267 96
1795798272 96
1795798277 96
1795798282 96
1795798287 96
1795798292 96
1795798297 96
1795798302 96
1795798307 94
1795798312 94
1795798317 94
1795798322 94
1795798327 94
1795798332 94
1795798337 94
1795798342 94
1795798347 94
1795798352 94
1795798357 94
1795798362 94
```
</details>

---

