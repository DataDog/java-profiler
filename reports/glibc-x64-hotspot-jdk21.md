---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:04:38 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1793203185 94
1793203190 94
1793203195 94
1793203200 94
1793203205 94
1793203210 94
1793203215 94
1793203220 94
1793203225 94
1793203230 94
1793203235 96
1793203240 96
1793203245 96
1793203250 96
1793203255 96
1793203260 91
1793203265 91
1793203270 91
1793203275 91
1793203280 91
```
</details>

---

