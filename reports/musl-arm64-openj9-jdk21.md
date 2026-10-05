---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 11:49:04 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 9 |
| Allocations | 217 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 10 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791215097 46
1791215102 46
1791215107 51
1791215112 51
1791215117 51
1791215122 51
1791215127 51
1791215132 51
1791215137 46
1791215142 46
1791215147 46
1791215152 46
1791215157 46
1791215162 46
1791215167 46
1791215172 46
1791215177 46
1791215182 46
1791215187 51
1791215192 51
```
</details>

---

