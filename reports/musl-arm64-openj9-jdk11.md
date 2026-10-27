---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:58:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 23-36 cores)</summary>

```
1793123637 25
1793123642 25
1793123647 25
1793123652 25
1793123657 25
1793123662 25
1793123668 25
1793123673 25
1793123678 25
1793123683 25
1793123688 25
1793123693 25
1793123698 25
1793123703 25
1793123708 25
1793123713 25
1793123718 36
1793123723 36
1793123728 23
1793123733 23
```
</details>

---

