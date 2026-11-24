---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 07:51:05 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 15 |
| Allocations | 92 |

<details>
<summary>CPU Timeline (3 unique values: 51-56 cores)</summary>

```
1795524372 53
1795524377 56
1795524382 56
1795524387 56
1795524392 56
1795524397 56
1795524402 56
1795524407 56
1795524412 56
1795524417 56
1795524422 56
1795524427 51
1795524432 51
1795524437 51
1795524442 51
1795524447 51
1795524452 51
1795524457 51
1795524462 51
1795524467 51
```
</details>

---

