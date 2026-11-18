---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 08:31:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1795008259 52
1795008264 52
1795008269 52
1795008274 52
1795008279 52
1795008284 52
1795008289 52
1795008294 52
1795008299 52
1795008304 52
1795008309 52
1795008314 52
1795008319 52
1795008324 52
1795008329 52
1795008334 52
1795008339 52
1795008344 52
1795008349 52
1795008354 52
```
</details>

---

