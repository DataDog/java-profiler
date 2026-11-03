---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 16:51:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1793742161 30
1793742166 30
1793742171 30
1793742176 30
1793742181 30
1793742186 30
1793742191 30
1793742196 30
1793742201 30
1793742206 30
1793742211 30
1793742216 30
1793742221 30
1793742226 30
1793742231 30
1793742236 30
1793742241 30
1793742246 30
1793742251 30
1793742256 30
```
</details>

---

