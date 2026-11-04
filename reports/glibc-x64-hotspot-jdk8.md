---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 08:54:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 38-40 cores)</summary>

```
1793800154 38
1793800159 38
1793800164 38
1793800169 38
1793800174 38
1793800179 38
1793800184 38
1793800189 38
1793800194 38
1793800199 38
1793800204 40
1793800209 40
1793800214 40
1793800219 40
1793800224 40
1793800229 40
1793800234 40
1793800239 40
1793800244 40
1793800249 40
```
</details>

---

