---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:40:13 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 14 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1795192434 64
1795192439 52
1795192444 52
1795192449 52
1795192454 52
1795192459 52
1795192464 52
1795192469 52
1795192474 52
1795192479 52
1795192484 52
1795192489 52
1795192494 52
1795192499 52
1795192504 52
1795192509 52
1795192514 52
1795192519 52
1795192524 52
1795192529 52
```
</details>

---

