---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:25:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 14 |
| Allocations | 94 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795015287 33
1795015292 33
1795015297 33
1795015302 33
1795015307 33
1795015312 33
1795015317 33
1795015322 33
1795015327 33
1795015332 33
1795015337 33
1795015342 33
1795015347 33
1795015352 33
1795015357 33
1795015362 38
1795015367 38
1795015372 38
1795015377 38
1795015382 38
```
</details>

---

