---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-05 13:29:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 11 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 14 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 69-80 cores)</summary>

```
1772735093 80
1772735098 80
1772735103 80
1772735108 78
1772735114 78
1772735119 78
1772735124 69
1772735129 69
1772735134 69
1772735139 75
1772735144 75
1772735149 75
1772735154 75
1772735159 75
1772735164 75
1772735169 75
1772735174 75
1772735179 75
1772735184 75
1772735189 75
```
</details>

---

