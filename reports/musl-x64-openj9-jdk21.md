---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 17:55:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1792100830 28
1792100835 28
1792100840 28
1792100845 28
1792100850 28
1792100855 28
1792100860 30
1792100865 30
1792100870 30
1792100875 30
1792100880 30
1792100885 30
1792100890 30
1792100895 30
1792100900 30
1792100905 30
1792100910 30
1792100915 30
1792100920 30
1792100925 30
```
</details>

---

