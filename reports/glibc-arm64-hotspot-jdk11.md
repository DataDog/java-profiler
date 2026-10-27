---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 11:01:34 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (1 unique values: 14-14 cores)</summary>

```
1793112866 14
1793112871 14
1793112876 14
1793112881 14
1793112886 14
1793112891 14
1793112896 14
1793112901 14
1793112906 14
1793112911 14
1793112916 14
1793112921 14
1793112926 14
1793112931 14
1793112936 14
1793112941 14
1793112946 14
1793112951 14
1793112956 14
1793112961 14
```
</details>

---

