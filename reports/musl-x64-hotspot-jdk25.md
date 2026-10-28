---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 12:04:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 80-85 cores)</summary>

```
1793203138 80
1793203143 80
1793203148 80
1793203153 85
1793203158 85
1793203163 85
1793203168 85
1793203173 85
1793203178 85
1793203183 85
1793203188 85
1793203193 85
1793203198 83
1793203203 83
1793203208 83
1793203213 83
1793203218 83
1793203223 83
1793203228 83
1793203233 83
```
</details>

---

