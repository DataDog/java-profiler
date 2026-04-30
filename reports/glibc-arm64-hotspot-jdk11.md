---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 05:30:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1777541163 32
1777541168 32
1777541173 32
1777541178 32
1777541183 32
1777541188 32
1777541193 32
1777541198 32
1777541203 32
1777541208 32
1777541213 32
1777541218 32
1777541223 32
1777541228 32
1777541233 32
1777541238 32
1777541243 32
1777541248 32
1777541253 32
1777541258 32
```
</details>

---

