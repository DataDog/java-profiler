---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-08 05:50:02 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786182259 27
1786182264 27
1786182269 32
1786182274 32
1786182279 32
1786182284 32
1786182289 32
1786182294 32
1786182299 32
1786182304 32
1786182309 32
1786182314 32
1786182319 32
1786182324 32
1786182329 32
1786182334 32
1786182339 32
1786182344 32
1786182349 32
1786182354 32
```
</details>

---

