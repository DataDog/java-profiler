---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:54:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
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
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1795798242 36
1795798247 36
1795798252 36
1795798257 36
1795798262 36
1795798267 36
1795798272 34
1795798277 34
1795798282 34
1795798287 34
1795798292 34
1795798297 34
1795798302 34
1795798307 34
1795798312 34
1795798317 34
1795798322 34
1795798327 34
1795798332 34
1795798337 34
```
</details>

---

