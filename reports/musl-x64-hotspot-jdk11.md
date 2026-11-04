---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 14:11:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
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
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793819147 32
1793819153 32
1793819158 32
1793819163 32
1793819168 32
1793819173 32
1793819178 32
1793819183 32
1793819188 32
1793819193 32
1793819198 32
1793819203 32
1793819208 32
1793819213 32
1793819218 32
1793819223 32
1793819228 32
1793819233 32
1793819238 32
1793819243 32
```
</details>

---

