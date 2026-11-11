---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 17:16:32 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 58-75 cores)</summary>

```
1794435112 60
1794435117 60
1794435122 60
1794435127 60
1794435132 60
1794435137 60
1794435142 60
1794435147 58
1794435152 58
1794435157 58
1794435162 58
1794435167 58
1794435172 58
1794435177 58
1794435182 58
1794435187 58
1794435192 58
1794435197 58
1794435202 58
1794435207 58
```
</details>

---

