---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 11:29:54 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 79-88 cores)</summary>

```
1793201085 79
1793201090 79
1793201095 84
1793201100 84
1793201105 84
1793201110 84
1793201115 84
1793201120 84
1793201125 82
1793201130 82
1793201135 82
1793201140 84
1793201145 84
1793201150 84
1793201155 84
1793201160 84
1793201165 84
1793201170 84
1793201175 84
1793201180 84
```
</details>

---

