---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 05:13:49 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 50-54 cores)</summary>

```
1793614105 54
1793614110 54
1793614115 54
1793614120 52
1793614125 52
1793614130 52
1793614135 52
1793614140 52
1793614145 52
1793614150 50
1793614155 50
1793614160 50
1793614165 50
1793614170 50
1793614175 50
1793614180 50
1793614185 50
1793614190 50
1793614195 50
1793614200 52
```
</details>

---

