---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-15 10:34:52 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 866 |
| Sample Rate | 14.43/sec |
| Health Score | 902% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1776263179 32
1776263184 32
1776263189 32
1776263194 32
1776263199 32
1776263204 32
1776263209 32
1776263214 32
1776263219 32
1776263224 32
1776263229 32
1776263234 32
1776263239 27
1776263244 27
1776263249 27
1776263254 27
1776263259 27
1776263264 24
1776263269 24
1776263274 24
```
</details>

---

