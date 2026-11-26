---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:09:25 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 86-96 cores)</summary>

```
1795691074 96
1795691079 96
1795691084 96
1795691089 96
1795691094 96
1795691099 96
1795691104 96
1795691109 96
1795691114 96
1795691119 96
1795691124 96
1795691129 96
1795691134 96
1795691139 96
1795691144 96
1795691149 96
1795691154 86
1795691159 86
1795691164 86
1795691169 86
```
</details>

---

