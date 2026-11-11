---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (6 unique values: 18-29 cores)</summary>

```
1794357152 27
1794357157 27
1794357162 27
1794357167 27
1794357172 29
1794357177 29
1794357182 20
1794357187 20
1794357192 20
1794357197 20
1794357202 20
1794357207 20
1794357212 20
1794357217 18
1794357222 18
1794357227 20
1794357232 20
1794357237 21
1794357242 21
1794357247 23
```
</details>

---

