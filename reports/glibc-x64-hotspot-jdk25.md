---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 14:05:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (4 unique values: 85-96 cores)</summary>

```
1795806094 87
1795806099 87
1795806104 87
1795806109 87
1795806114 87
1795806119 87
1795806124 87
1795806129 87
1795806134 87
1795806139 87
1795806144 85
1795806149 85
1795806154 85
1795806159 85
1795806164 96
1795806169 96
1795806174 96
1795806179 94
1795806184 94
1795806189 94
```
</details>

---

