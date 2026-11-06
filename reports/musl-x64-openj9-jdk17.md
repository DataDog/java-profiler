---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-06 16:43:57 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (5 unique values: 22-60 cores)</summary>

```
1794001093 24
1794001098 24
1794001103 24
1794001108 24
1794001113 24
1794001118 24
1794001123 24
1794001128 24
1794001133 24
1794001138 24
1794001143 24
1794001148 24
1794001153 24
1794001158 22
1794001163 22
1794001168 42
1794001173 42
1794001178 42
1794001183 42
1794001188 42
```
</details>

---

