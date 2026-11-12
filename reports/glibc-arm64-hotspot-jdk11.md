---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 06:55:44 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 12 |
| Allocations | 175 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794484083 31
1794484088 31
1794484093 31
1794484098 31
1794484103 31
1794484108 31
1794484113 31
1794484118 31
1794484123 31
1794484128 31
1794484133 31
1794484138 31
1794484143 36
1794484148 36
1794484153 36
1794484158 36
1794484163 36
1794484168 36
1794484173 36
1794484178 36
```
</details>

---

