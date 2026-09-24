---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-24 05:34:56 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 34-40 cores)</summary>

```
1790242186 40
1790242191 40
1790242196 40
1790242201 40
1790242206 40
1790242211 40
1790242216 40
1790242221 40
1790242226 40
1790242231 40
1790242236 40
1790242241 40
1790242246 40
1790242251 40
1790242256 40
1790242261 40
1790242266 40
1790242271 34
1790242276 34
1790242281 34
```
</details>

---

