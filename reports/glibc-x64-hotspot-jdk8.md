---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-30 13:48:57 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793382235 49
1793382240 49
1793382245 49
1793382250 49
1793382255 49
1793382260 49
1793382265 51
1793382270 51
1793382275 51
1793382280 51
1793382285 51
1793382290 51
1793382295 51
1793382300 51
1793382305 51
1793382310 51
1793382315 51
1793382320 51
1793382325 51
1793382330 51
```
</details>

---

