---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 08:54:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793800138 46
1793800143 46
1793800148 46
1793800153 46
1793800158 46
1793800163 46
1793800168 46
1793800173 48
1793800178 48
1793800183 48
1793800188 48
1793800193 48
1793800198 48
1793800203 48
1793800208 48
1793800213 48
1793800218 48
1793800223 48
1793800228 48
1793800233 48
```
</details>

---

