---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-06-10 05:13:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 14 |
| Allocations | 96 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1781082609 60
1781082614 60
1781082619 60
1781082624 60
1781082629 60
1781082634 60
1781082639 60
1781082644 60
1781082649 60
1781082654 60
1781082659 64
1781082664 64
1781082669 64
1781082674 64
1781082679 64
1781082684 64
1781082689 64
1781082694 64
1781082699 64
1781082704 64
```
</details>

---

