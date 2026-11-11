---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 17:16:30 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 19-23 cores)</summary>

```
1794435134 23
1794435139 23
1794435144 23
1794435149 23
1794435154 23
1794435159 23
1794435164 23
1794435169 23
1794435174 23
1794435179 21
1794435184 21
1794435189 21
1794435194 21
1794435199 21
1794435204 21
1794435209 21
1794435214 21
1794435219 23
1794435224 23
1794435229 23
```
</details>

---

