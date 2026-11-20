---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 11:40:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795192434 50
1795192439 50
1795192444 50
1795192449 50
1795192454 50
1795192459 50
1795192464 50
1795192469 50
1795192474 50
1795192479 50
1795192484 50
1795192489 50
1795192494 50
1795192499 50
1795192504 50
1795192509 50
1795192514 50
1795192519 50
1795192524 50
1795192529 50
```
</details>

---

