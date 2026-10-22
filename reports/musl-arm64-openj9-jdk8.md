---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 06:47:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1792665774 51
1792665779 51
1792665784 51
1792665789 51
1792665794 51
1792665799 51
1792665804 51
1792665809 51
1792665814 51
1792665819 51
1792665824 51
1792665829 51
1792665834 51
1792665839 51
1792665844 51
1792665849 51
1792665854 51
1792665859 51
1792665864 51
1792665869 39
```
</details>

---

