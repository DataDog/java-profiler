---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 12:28:41 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 58-60 cores)</summary>

```
1792772650 60
1792772655 60
1792772660 60
1792772665 60
1792772670 60
1792772675 60
1792772680 60
1792772685 60
1792772690 60
1792772695 60
1792772700 60
1792772705 60
1792772710 60
1792772715 60
1792772720 58
1792772725 58
1792772730 58
1792772735 58
1792772740 58
1792772745 58
```
</details>

---

