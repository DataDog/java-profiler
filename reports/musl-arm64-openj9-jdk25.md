---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:48:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 13 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794930047 51
1794930052 51
1794930057 51
1794930062 51
1794930067 51
1794930072 51
1794930077 38
1794930082 38
1794930087 51
1794930092 51
1794930097 51
1794930102 51
1794930107 51
1794930113 51
1794930118 51
1794930123 51
1794930128 51
1794930133 51
1794930138 51
1794930143 51
```
</details>

---

