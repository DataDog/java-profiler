---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:54:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 62-83 cores)</summary>

```
1795798252 71
1795798257 71
1795798262 71
1795798267 71
1795798272 71
1795798277 71
1795798282 71
1795798287 71
1795798292 71
1795798297 71
1795798302 62
1795798307 62
1795798312 62
1795798317 62
1795798322 62
1795798327 62
1795798332 62
1795798337 62
1795798342 62
1795798347 62
```
</details>

---

