---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-06 16:43:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1794001113 61
1794001118 61
1794001123 61
1794001128 61
1794001133 61
1794001138 61
1794001143 61
1794001148 63
1794001153 63
1794001158 63
1794001163 63
1794001168 63
1794001173 63
1794001178 63
1794001183 63
1794001188 63
1794001193 63
1794001198 63
1794001203 63
1794001208 63
```
</details>

---

