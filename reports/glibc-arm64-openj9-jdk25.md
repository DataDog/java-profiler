---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:25:44 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 86 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1795015317 38
1795015322 38
1795015327 38
1795015332 38
1795015337 38
1795015342 38
1795015347 38
1795015352 38
1795015357 38
1795015362 38
1795015367 38
1795015372 38
1795015377 38
1795015382 38
1795015387 38
1795015393 38
1795015398 38
1795015403 51
1795015408 51
1795015413 51
```
</details>

---

