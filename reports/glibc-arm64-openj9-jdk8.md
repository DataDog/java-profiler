---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-30 21:23:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1788139232 32
1788139237 32
1788139242 32
1788139247 32
1788139252 32
1788139257 32
1788139262 32
1788139267 32
1788139272 32
1788139277 32
1788139282 32
1788139287 32
1788139292 32
1788139297 32
1788139302 32
1788139307 32
1788139312 32
1788139317 32
1788139322 32
1788139327 27
```
</details>

---

