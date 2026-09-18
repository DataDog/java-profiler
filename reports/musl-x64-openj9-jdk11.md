---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:34:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1789716441 81
1789716446 81
1789716451 81
1789716456 79
1789716461 79
1789716466 79
1789716471 79
1789716476 79
1789716481 79
1789716486 79
1789716491 79
1789716496 79
1789716501 79
1789716506 77
1789716511 77
1789716516 77
1789716521 77
1789716526 77
1789716531 77
1789716536 77
```
</details>

---

