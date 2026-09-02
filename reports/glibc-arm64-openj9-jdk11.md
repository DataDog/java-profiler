---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 14:43:41 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
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
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1788374382 45
1788374387 45
1788374392 45
1788374397 45
1788374402 45
1788374407 45
1788374412 45
1788374417 45
1788374422 45
1788374427 45
1788374432 45
1788374437 45
1788374442 45
1788374447 45
1788374452 45
1788374457 45
1788374462 45
1788374467 45
1788374472 45
1788374477 45
```
</details>

---

