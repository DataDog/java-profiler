---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 09:24:33 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 9 |
| Allocations | 187 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795702868 47
1795702873 47
1795702878 47
1795702883 47
1795702888 47
1795702893 47
1795702898 47
1795702903 47
1795702908 47
1795702913 47
1795702918 47
1795702923 47
1795702928 47
1795702933 47
1795702938 47
1795702943 47
1795702948 64
1795702953 64
1795702958 64
1795702963 64
```
</details>

---

