---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 06:19:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 79-96 cores)</summary>

```
1790244804 79
1790244809 79
1790244814 79
1790244819 79
1790244824 79
1790244829 79
1790244834 79
1790244839 79
1790244844 79
1790244849 79
1790244854 89
1790244859 89
1790244864 89
1790244869 89
1790244874 89
1790244879 89
1790244884 89
1790244889 89
1790244894 89
1790244899 96
```
</details>

---

