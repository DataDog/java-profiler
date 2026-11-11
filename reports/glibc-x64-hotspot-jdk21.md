---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 15:02:14 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1794427084 74
1794427089 74
1794427094 74
1794427099 74
1794427104 74
1794427109 74
1794427114 74
1794427119 74
1794427124 74
1794427129 74
1794427134 74
1794427139 74
1794427144 74
1794427149 74
1794427154 74
1794427159 74
1794427164 74
1794427169 74
1794427174 74
1794427179 72
```
</details>

---

