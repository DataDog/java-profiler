---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 12:44:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 35-42 cores)</summary>

```
1793291799 42
1793291804 42
1793291809 42
1793291814 39
1793291819 39
1793291824 39
1793291829 39
1793291834 39
1793291839 39
1793291844 35
1793291849 35
1793291854 35
1793291859 35
1793291864 35
1793291869 35
1793291874 40
1793291879 40
1793291884 40
1793291889 40
1793291894 40
```
</details>

---

