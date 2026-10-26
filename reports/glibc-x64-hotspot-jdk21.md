---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 16:16:44 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 88-96 cores)</summary>

```
1793045176 88
1793045181 88
1793045186 88
1793045191 88
1793045196 90
1793045201 90
1793045206 90
1793045211 92
1793045216 92
1793045221 92
1793045226 92
1793045231 92
1793045236 92
1793045241 92
1793045246 92
1793045251 94
1793045256 94
1793045261 94
1793045266 96
1793045271 96
```
</details>

---

