---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 12:19:03 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (4 unique values: 72-96 cores)</summary>

```
1794590087 94
1794590092 94
1794590097 94
1794590102 96
1794590107 96
1794590112 96
1794590117 96
1794590122 96
1794590127 96
1794590132 90
1794590137 90
1794590142 90
1794590147 90
1794590152 90
1794590157 90
1794590162 94
1794590167 94
1794590172 94
1794590177 94
1794590182 94
```
</details>

---

