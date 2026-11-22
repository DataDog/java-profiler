---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 05:47:55 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1795344224 34
1795344229 34
1795344234 34
1795344239 34
1795344244 34
1795344249 34
1795344254 34
1795344259 34
1795344264 34
1795344269 34
1795344274 34
1795344279 34
1795344284 32
1795344289 32
1795344294 32
1795344299 32
1795344304 32
1795344309 32
1795344314 32
1795344319 32
```
</details>

---

