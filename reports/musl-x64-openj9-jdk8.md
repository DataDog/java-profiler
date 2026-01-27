---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-01-27 09:00:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1769514141 27
1769514146 27
1769514151 27
1769514156 27
1769514161 27
1769514166 32
1769514171 32
1769514176 27
1769514181 27
1769514186 27
1769514191 27
1769514196 27
1769514201 27
1769514206 27
1769514211 27
1769514216 27
1769514221 27
1769514226 27
1769514231 27
1769514236 27
```
</details>

---

