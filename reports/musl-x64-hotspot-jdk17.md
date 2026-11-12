---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 08:02:22 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 66-70 cores)</summary>

```
1794488194 70
1794488199 70
1794488204 70
1794488209 70
1794488214 70
1794488219 70
1794488224 70
1794488229 68
1794488234 68
1794488239 68
1794488244 68
1794488249 68
1794488254 68
1794488259 68
1794488264 68
1794488269 66
1794488274 66
1794488279 66
1794488284 66
1794488289 66
```
</details>

---

