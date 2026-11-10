---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 14:54:01 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794340127 32
1794340132 32
1794340137 32
1794340142 32
1794340147 32
1794340152 32
1794340157 30
1794340162 30
1794340167 30
1794340172 30
1794340177 30
1794340182 30
1794340187 30
1794340192 30
1794340197 30
1794340202 30
1794340207 30
1794340212 30
1794340217 30
1794340222 30
```
</details>

---

