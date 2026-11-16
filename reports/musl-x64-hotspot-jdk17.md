---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-15 21:18:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 76-79 cores)</summary>

```
1794795160 76
1794795165 76
1794795170 76
1794795175 76
1794795180 76
1794795185 76
1794795190 76
1794795195 76
1794795200 79
1794795205 79
1794795210 79
1794795215 79
1794795220 79
1794795225 79
1794795230 79
1794795235 77
1794795240 77
1794795245 77
1794795250 77
1794795255 77
```
</details>

---

