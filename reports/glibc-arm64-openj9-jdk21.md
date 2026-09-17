---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 19:15:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1789686674 30
1789686679 30
1789686684 30
1789686689 30
1789686694 30
1789686699 30
1789686704 30
1789686709 30
1789686714 30
1789686719 30
1789686724 30
1789686729 30
1789686734 30
1789686739 30
1789686744 30
1789686749 30
1789686754 30
1789686759 30
1789686764 30
1789686769 30
```
</details>

---

