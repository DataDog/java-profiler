---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 06:12:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 9-32 cores)</summary>

```
1789639628 9
1789639633 9
1789639638 9
1789639643 9
1789639648 9
1789639653 9
1789639658 9
1789639663 9
1789639668 9
1789639674 9
1789639679 9
1789639684 9
1789639689 9
1789639694 9
1789639699 9
1789639704 32
1789639709 32
1789639714 32
1789639719 32
1789639724 32
```
</details>

---

