---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 05:42:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 15 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 40-51 cores)</summary>

```
1793875149 40
1793875154 40
1793875159 40
1793875164 40
1793875169 51
1793875174 51
1793875179 51
1793875184 40
1793875189 40
1793875194 40
1793875199 40
1793875204 40
1793875209 40
1793875214 40
1793875219 40
1793875224 40
1793875229 40
1793875234 40
1793875239 40
1793875244 40
```
</details>

---

