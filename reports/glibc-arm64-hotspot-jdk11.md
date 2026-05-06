---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-06 19:44:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 12 |
| Allocations | 172 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
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
1778110872 64
1778110877 64
1778110882 64
1778110887 64
1778110892 64
1778110897 64
```
</details>

---

