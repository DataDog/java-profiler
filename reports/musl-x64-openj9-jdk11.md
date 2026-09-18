---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:33:38 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 84-94 cores)</summary>

```
1789716496 84
1789716501 84
1789716506 94
1789716511 94
1789716516 94
1789716521 94
1789716527 94
1789716532 94
1789716537 94
1789716542 94
1789716547 94
1789716552 94
1789716557 94
1789716562 94
1789716567 94
1789716572 94
1789716577 92
1789716582 92
1789716587 92
1789716592 92
```
</details>

---

