---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 06:28:25 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 12 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 34-38 cores)</summary>

```
1795087360 37
1795087365 37
1795087370 37
1795087375 37
1795087380 37
1795087385 37
1795087390 38
1795087395 38
1795087400 38
1795087405 38
1795087410 37
1795087415 37
1795087420 34
1795087425 34
1795087430 34
1795087435 34
1795087440 34
1795087445 34
1795087450 34
1795087455 34
```
</details>

---

