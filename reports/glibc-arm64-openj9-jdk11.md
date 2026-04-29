---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 11:49:26 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 11 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777477389 59
1777477394 59
1777477399 59
1777477404 59
1777477409 59
1777477414 59
1777477419 59
1777477424 59
1777477429 59
1777477434 64
1777477439 64
1777477444 64
1777477449 64
1777477454 64
1777477459 64
1777477464 64
1777477469 64
1777477474 64
1777477479 64
1777477484 64
```
</details>

---

