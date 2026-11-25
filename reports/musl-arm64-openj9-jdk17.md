---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:00:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 10 |
| Allocations | 111 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795618457 28
1795618462 28
1795618467 28
1795618472 28
1795618477 28
1795618482 28
1795618487 28
1795618492 28
1795618497 28
1795618502 28
1795618507 28
1795618512 33
1795618517 33
1795618522 33
1795618527 33
1795618532 33
1795618537 33
1795618542 33
1795618547 33
1795618552 33
```
</details>

---

