---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:20:29 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857349 64
1777857354 64
1777857359 64
1777857364 64
1777857369 64
1777857374 64
1777857379 64
1777857384 64
1777857389 64
1777857394 64
1777857399 64
1777857404 64
1777857409 64
1777857414 64
1777857419 64
1777857424 64
1777857429 64
1777857434 64
1777857439 64
1777857444 64
```
</details>

---

