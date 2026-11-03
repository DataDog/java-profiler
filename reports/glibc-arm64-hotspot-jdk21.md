---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 12:51:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 11 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793728027 46
1793728032 46
1793728037 46
1793728042 46
1793728047 46
1793728052 46
1793728057 46
1793728062 51
1793728067 51
1793728072 51
1793728077 51
1793728082 51
1793728087 51
1793728092 51
1793728097 51
1793728102 51
1793728107 51
1793728112 51
1793728117 51
1793728122 51
```
</details>

---

