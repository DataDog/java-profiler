---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 17:16:30 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 58-75 cores)</summary>

```
1794435119 60
1794435124 60
1794435129 60
1794435134 60
1794435139 60
1794435144 60
1794435149 58
1794435154 58
1794435159 58
1794435164 58
1794435169 58
1794435174 58
1794435179 58
1794435184 58
1794435189 58
1794435194 58
1794435199 58
1794435204 58
1794435209 58
1794435214 58
```
</details>

---

