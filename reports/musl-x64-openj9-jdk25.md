---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 12:04:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793203138 32
1793203143 32
1793203148 32
1793203153 32
1793203158 32
1793203163 32
1793203168 32
1793203173 32
1793203178 32
1793203183 32
1793203188 32
1793203193 32
1793203198 32
1793203203 32
1793203208 32
1793203213 32
1793203218 32
1793203223 32
1793203228 32
1793203233 32
```
</details>

---

