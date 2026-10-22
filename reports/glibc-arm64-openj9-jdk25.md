---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 06:46:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1792665779 43
1792665784 47
1792665789 47
1792665794 47
1792665799 47
1792665804 47
1792665809 42
1792665814 42
1792665819 42
1792665824 42
1792665829 42
1792665834 42
1792665839 42
1792665844 42
1792665849 43
1792665854 43
1792665859 43
1792665864 48
1792665869 48
1792665874 48
```
</details>

---

