---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-27 09:00:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 15.63/sec |
| Health Score | 977% |
| Threads | 8 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 23.07/sec |
| Health Score | 1442% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1769514126 46
1769514131 46
1769514136 46
1769514141 46
1769514146 46
1769514151 46
1769514156 46
1769514161 46
1769514166 46
1769514171 46
1769514176 41
1769514181 41
1769514186 41
1769514191 41
1769514196 41
1769514201 41
1769514206 41
1769514211 41
1769514216 41
1769514221 41
```
</details>

---

