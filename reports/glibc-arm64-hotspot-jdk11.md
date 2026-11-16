---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:34:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794850177 51
1794850182 51
1794850187 51
1794850192 51
1794850197 51
1794850202 46
1794850207 46
1794850212 46
1794850217 46
1794850222 46
1794850227 46
1794850232 46
1794850237 46
1794850242 46
1794850247 46
1794850252 46
1794850257 46
1794850262 46
1794850267 51
1794850272 51
```
</details>

---

