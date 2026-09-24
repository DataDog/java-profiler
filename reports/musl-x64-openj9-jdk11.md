---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:40:56 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 43-96 cores)</summary>

```
1790238970 43
1790238975 43
1790238980 43
1790238985 76
1790238990 76
1790238995 76
1790239000 76
1790239005 76
1790239010 76
1790239015 76
1790239020 76
1790239025 76
1790239030 76
1790239035 77
1790239040 77
1790239045 77
1790239050 77
1790239055 77
1790239060 77
1790239065 77
```
</details>

---

