---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 16:43:56 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 11 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794001111 40
1794001116 40
1794001121 40
1794001126 40
1794001131 40
1794001136 40
1794001141 40
1794001146 40
1794001151 40
1794001156 40
1794001161 40
1794001166 40
1794001171 40
1794001176 40
1794001181 40
1794001186 40
1794001191 40
1794001196 40
1794001201 40
1794001206 40
```
</details>

---

