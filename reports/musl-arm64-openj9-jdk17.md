---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:44:21 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1789731623 10
1789731628 10
1789731633 10
1789731638 10
1789731643 10
1789731648 10
1789731653 10
1789731658 10
1789731663 10
1789731668 10
1789731673 10
1789731678 30
1789731683 30
1789731688 30
1789731693 30
1789731698 30
1789731703 30
1789731708 30
1789731713 30
1789731718 30
```
</details>

---

