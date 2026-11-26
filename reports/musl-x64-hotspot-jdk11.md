---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 05:52:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 31-59 cores)</summary>

```
1795690067 31
1795690072 31
1795690077 31
1795690082 31
1795690087 31
1795690092 31
1795690097 31
1795690102 59
1795690107 59
1795690112 59
1795690117 59
1795690122 59
1795690127 59
1795690132 59
1795690137 59
1795690142 59
1795690147 59
1795690152 59
1795690157 59
1795690162 59
```
</details>

---

