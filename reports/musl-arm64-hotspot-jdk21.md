---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 06:43:03 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 10 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793011042 46
1793011047 46
1793011052 46
1793011057 46
1793011062 46
1793011067 46
1793011072 46
1793011077 46
1793011082 46
1793011087 46
1793011092 46
1793011097 46
1793011102 46
1793011107 46
1793011112 46
1793011117 46
1793011122 46
1793011127 46
1793011132 46
1793011137 48
```
</details>

---

