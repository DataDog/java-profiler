---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-06 19:44:03 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778110772 64
1778110777 64
1778110782 64
1778110787 64
1778110792 64
1778110797 64
1778110802 64
1778110807 64
1778110812 64
1778110817 64
1778110822 64
1778110827 64
1778110832 64
1778110837 64
1778110842 64
1778110847 64
1778110852 64
1778110857 64
1778110862 64
1778110867 64
```
</details>

---

