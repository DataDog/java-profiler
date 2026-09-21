---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 04:46:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (4 unique values: 10-32 cores)</summary>

```
1789980049 10
1789980054 10
1789980059 25
1789980064 25
1789980069 25
1789980074 25
1789980079 30
1789980084 30
1789980089 30
1789980094 30
1789980099 32
1789980104 32
1789980109 32
1789980114 32
1789980119 32
1789980124 32
1789980129 32
1789980134 32
1789980139 32
1789980144 32
```
</details>

---

