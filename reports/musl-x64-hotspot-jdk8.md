---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-06 13:09:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1791306171 62
1791306176 62
1791306181 62
1791306186 62
1791306191 62
1791306196 62
1791306201 62
1791306206 64
1791306211 64
1791306216 64
1791306221 64
1791306226 64
1791306231 64
1791306236 64
1791306241 64
1791306246 64
1791306251 64
1791306256 64
1791306261 64
1791306266 64
```
</details>

---

