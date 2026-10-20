---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 17:39:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 73-78 cores)</summary>

```
1792532121 73
1792532126 73
1792532131 73
1792532136 73
1792532141 73
1792532146 75
1792532151 75
1792532156 75
1792532161 78
1792532166 78
1792532171 78
1792532176 78
1792532181 76
1792532186 76
1792532191 76
1792532196 76
1792532201 76
1792532206 76
1792532211 76
1792532216 76
```
</details>

---

