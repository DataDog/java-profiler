---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:46:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 7 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 34-44 cores)</summary>

```
1789980044 34
1789980049 34
1789980054 34
1789980059 34
1789980064 43
1789980069 43
1789980074 43
1789980079 43
1789980084 43
1789980089 43
1789980094 43
1789980099 43
1789980104 43
1789980109 43
1789980114 43
1789980119 43
1789980124 43
1789980129 43
1789980134 44
1789980139 44
```
</details>

---

