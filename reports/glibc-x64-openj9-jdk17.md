---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 19:15:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 65-96 cores)</summary>

```
1789686649 65
1789686654 65
1789686659 65
1789686664 88
1789686669 88
1789686674 88
1789686679 88
1789686684 88
1789686689 88
1789686694 88
1789686699 96
1789686704 96
1789686709 96
1789686714 96
1789686719 96
1789686724 96
1789686729 96
1789686734 96
1789686739 96
1789686744 96
```
</details>

---

