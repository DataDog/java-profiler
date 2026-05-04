---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:20:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777857348 59
1777857353 59
1777857358 59
1777857363 59
1777857368 59
1777857373 59
1777857378 59
1777857383 59
1777857388 59
1777857393 59
1777857398 59
1777857403 59
1777857408 59
1777857413 59
1777857418 64
1777857423 64
1777857428 64
1777857433 64
1777857438 64
1777857443 64
```
</details>

---

