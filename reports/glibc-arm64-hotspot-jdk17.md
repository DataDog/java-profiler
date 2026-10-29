---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 09:55:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 36-40 cores)</summary>

```
1793281784 36
1793281789 36
1793281794 36
1793281799 36
1793281804 36
1793281809 36
1793281814 36
1793281819 36
1793281824 36
1793281829 36
1793281834 36
1793281839 36
1793281844 40
1793281849 40
1793281854 40
1793281859 40
1793281864 40
1793281869 40
1793281874 38
1793281879 38
```
</details>

---

