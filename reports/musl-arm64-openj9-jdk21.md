---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-16 07:30:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 10 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1789557839 48
1789557844 48
1789557849 48
1789557854 48
1789557859 48
1789557864 48
1789557869 47
1789557874 47
1789557879 47
1789557884 47
1789557890 47
1789557895 47
1789557900 48
1789557905 48
1789557910 48
1789557915 48
1789557920 48
1789557925 48
1789557930 48
1789557935 48
```
</details>

---

