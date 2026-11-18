---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:59:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 49-55 cores)</summary>

```
1794999176 49
1794999181 51
1794999186 51
1794999191 51
1794999196 51
1794999201 51
1794999206 51
1794999211 51
1794999216 51
1794999221 51
1794999226 51
1794999231 51
1794999236 51
1794999241 51
1794999246 53
1794999251 53
1794999256 55
1794999261 55
1794999266 55
1794999271 55
```
</details>

---

