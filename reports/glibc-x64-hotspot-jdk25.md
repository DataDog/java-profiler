---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 11:32:47 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (5 unique values: 67-79 cores)</summary>

```
1795192088 67
1795192093 67
1795192098 67
1795192103 67
1795192108 67
1795192113 67
1795192118 67
1795192124 67
1795192129 67
1795192134 67
1795192139 67
1795192144 76
1795192149 76
1795192154 76
1795192159 76
1795192164 79
1795192169 79
1795192174 79
1795192179 77
1795192184 77
```
</details>

---

