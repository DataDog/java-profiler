---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 06:38:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791541826 40
1791541832 40
1791541837 40
1791541842 40
1791541847 40
1791541852 40
1791541857 40
1791541862 40
1791541867 40
1791541872 40
1791541877 40
1791541882 40
1791541887 40
1791541892 40
1791541897 40
1791541902 40
1791541907 40
1791541912 40
1791541917 40
1791541922 40
```
</details>

---

