---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 14:54:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1794340158 96
1794340163 96
1794340168 96
1794340173 96
1794340178 96
1794340183 96
1794340188 96
1794340193 96
1794340198 94
1794340203 94
1794340208 92
1794340214 92
1794340219 92
1794340224 92
1794340229 92
1794340234 92
1794340239 92
1794340244 92
1794340249 92
1794340254 92
```
</details>

---

