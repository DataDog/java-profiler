---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 12:04:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 10 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (7 unique values: 28-62 cores)</summary>

```
1793203193 30
1793203198 30
1793203203 30
1793203208 30
1793203213 30
1793203218 30
1793203223 30
1793203228 30
1793203233 30
1793203238 30
1793203243 29
1793203248 29
1793203253 28
1793203258 28
1793203263 28
1793203268 62
1793203273 62
1793203278 62
1793203283 62
1793203288 57
```
</details>

---

