---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:22:12 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790093714 32
1790093719 32
1790093724 32
1790093729 32
1790093734 32
1790093739 32
1790093744 32
1790093749 32
1790093754 32
1790093759 32
1790093764 32
1790093769 32
1790093774 32
1790093779 32
1790093784 32
1790093789 32
1790093794 32
1790093799 32
1790093804 32
1790093809 32
```
</details>

---

