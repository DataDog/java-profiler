---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:09:23 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 66-72 cores)</summary>

```
1795691089 72
1795691094 72
1795691099 72
1795691104 72
1795691109 72
1795691114 72
1795691119 72
1795691124 72
1795691129 72
1795691134 72
1795691139 66
1795691144 66
1795691149 66
1795691154 66
1795691159 66
1795691164 66
1795691169 66
1795691174 66
1795691179 66
1795691184 66
```
</details>

---

