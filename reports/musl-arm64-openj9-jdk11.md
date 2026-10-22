---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 06:47:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 10 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 42-54 cores)</summary>

```
1792665779 54
1792665784 54
1792665789 54
1792665794 54
1792665799 54
1792665804 54
1792665809 54
1792665814 54
1792665819 54
1792665824 54
1792665829 54
1792665834 54
1792665839 54
1792665844 54
1792665849 54
1792665854 54
1792665859 54
1792665864 54
1792665869 54
1792665874 54
```
</details>

---

