---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 06:55:47 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 44-63 cores)</summary>

```
1794484073 63
1794484078 63
1794484083 63
1794484088 46
1794484093 46
1794484098 46
1794484103 46
1794484108 46
1794484113 46
1794484118 44
1794484123 44
1794484128 44
1794484133 44
1794484138 44
1794484143 44
1794484148 44
1794484153 44
1794484158 44
1794484163 44
1794484168 44
```
</details>

---

