---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:09:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 7 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1795691079 28
1795691084 28
1795691089 28
1795691094 30
1795691099 30
1795691104 30
1795691109 30
1795691114 30
1795691119 30
1795691124 30
1795691129 30
1795691134 30
1795691139 30
1795691144 30
1795691149 30
1795691154 30
1795691159 30
1795691164 30
1795691169 30
1795691174 30
```
</details>

---

