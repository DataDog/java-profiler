---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 05:52:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 9 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (3 unique values: 42-53 cores)</summary>

```
1795690079 53
1795690084 44
1795690089 44
1795690094 42
1795690099 42
1795690104 42
1795690109 42
1795690114 44
1795690119 44
1795690124 44
1795690129 44
1795690134 44
1795690139 44
1795690144 44
1795690149 44
1795690154 44
1795690159 44
1795690164 44
1795690169 44
1795690174 44
```
</details>

---

