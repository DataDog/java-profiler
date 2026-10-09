---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 06:38:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1791541827 10
1791541832 10
1791541837 10
1791541842 10
1791541847 10
1791541852 10
1791541857 10
1791541862 10
1791541867 10
1791541872 10
1791541877 30
1791541882 30
1791541887 30
1791541892 30
1791541897 30
1791541902 30
1791541907 30
1791541912 30
1791541917 30
1791541922 30
```
</details>

---

