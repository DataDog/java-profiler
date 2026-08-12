---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-12 04:18:24 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 10 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1786522371 48
1786522376 48
1786522381 43
1786522386 43
1786522391 43
1786522396 43
1786522401 43
1786522406 43
1786522411 43
1786522416 43
1786522421 43
1786522426 43
1786522431 42
1786522436 42
1786522441 42
1786522446 42
1786522451 42
1786522456 42
1786522461 42
1786522466 42
```
</details>

---

