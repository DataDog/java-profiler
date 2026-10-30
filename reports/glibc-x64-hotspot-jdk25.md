---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 07:23:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793359145 30
1793359150 30
1793359155 32
1793359160 32
1793359165 32
1793359170 32
1793359175 32
1793359180 32
1793359185 32
1793359190 32
1793359195 32
1793359200 32
1793359205 32
1793359210 32
1793359215 32
1793359220 32
1793359225 32
1793359230 32
1793359235 32
1793359240 32
```
</details>

---

