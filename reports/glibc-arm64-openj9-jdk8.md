---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-08 05:50:02 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786182258 27
1786182263 27
1786182268 32
1786182273 32
1786182278 32
1786182283 32
1786182288 32
1786182293 32
1786182298 32
1786182303 32
1786182308 32
1786182313 32
1786182318 32
1786182323 32
1786182328 32
1786182333 32
1786182338 32
1786182343 32
1786182348 32
1786182353 32
```
</details>

---

