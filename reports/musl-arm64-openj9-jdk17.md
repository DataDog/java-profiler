---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 20:28:23 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 12 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793755439 30
1793755444 30
1793755449 30
1793755454 30
1793755459 30
1793755464 30
1793755469 30
1793755474 30
1793755479 30
1793755484 30
1793755489 30
1793755494 30
1793755499 30
1793755504 30
1793755509 30
1793755514 30
1793755519 30
1793755524 30
1793755529 30
1793755534 30
```
</details>

---

