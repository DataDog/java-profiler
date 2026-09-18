---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:38:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 48-81 cores)</summary>

```
1789716466 48
1789716471 48
1789716476 48
1789716481 48
1789716486 48
1789716491 48
1789716496 48
1789716501 48
1789716506 81
1789716511 81
1789716516 81
1789716521 81
1789716526 81
1789716531 81
1789716536 81
1789716541 81
1789716546 81
1789716551 81
1789716556 81
1789716561 81
```
</details>

---

