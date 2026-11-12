---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 09:43:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 941 |
| Sample Rate | 15.68/sec |
| Health Score | 980% |
| Threads | 10 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1794494099 86
1794494104 86
1794494109 86
1794494114 86
1794494119 86
1794494124 86
1794494129 86
1794494134 86
1794494139 86
1794494144 86
1794494149 86
1794494154 86
1794494159 86
1794494164 86
1794494169 86
1794494174 86
1794494179 84
1794494184 84
1794494189 84
1794494195 84
```
</details>

---

