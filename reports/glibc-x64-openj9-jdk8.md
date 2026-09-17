---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 19:15:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 164 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 65-96 cores)</summary>

```
1789686624 65
1789686629 65
1789686634 65
1789686639 65
1789686644 65
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
```
</details>

---

