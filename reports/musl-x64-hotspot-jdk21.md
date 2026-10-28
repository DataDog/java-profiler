---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:04:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
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
1793203223 30
1793203228 30
1793203233 30
1793203238 30
```
</details>

---

