---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-15 20:26:53 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 11 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794792172 40
1794792177 40
1794792182 40
1794792187 40
1794792192 40
1794792197 40
1794792202 40
1794792207 40
1794792212 40
1794792217 40
1794792222 40
1794792227 40
1794792232 40
1794792237 40
1794792242 40
1794792247 40
1794792252 40
1794792257 40
1794792262 40
1794792267 40
```
</details>

---

