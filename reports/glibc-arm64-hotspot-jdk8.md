---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-27 11:54:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795798277 47
1795798282 47
1795798287 47
1795798292 47
1795798297 47
1795798302 47
1795798307 47
1795798312 47
1795798317 47
1795798322 47
1795798327 47
1795798332 47
1795798337 47
1795798342 47
1795798347 47
1795798352 47
1795798357 47
1795798362 47
1795798367 47
1795798372 47
```
</details>

---

