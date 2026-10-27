---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 11:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 6 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (1 unique values: 6-6 cores)</summary>

```
1793115749 6
1793115754 6
1793115759 6
1793115764 6
1793115769 6
1793115774 6
1793115779 6
1793115784 6
1793115789 6
1793115794 6
1793115799 6
1793115804 6
1793115809 6
1793115814 6
1793115819 6
1793115824 6
1793115829 6
1793115834 6
1793115839 6
1793115844 6
```
</details>

---

