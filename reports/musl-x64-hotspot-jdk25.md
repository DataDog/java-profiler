---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 20:26:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794792137 32
1794792142 32
1794792147 32
1794792152 32
1794792157 32
1794792162 32
1794792167 32
1794792172 32
1794792177 32
1794792182 32
1794792187 32
1794792192 32
1794792197 32
1794792202 32
1794792207 32
1794792212 32
1794792217 32
1794792222 32
1794792227 32
1794792232 32
```
</details>

---

