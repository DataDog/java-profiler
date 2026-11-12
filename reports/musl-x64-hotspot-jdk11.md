---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:02:22 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 928 |
| Sample Rate | 15.47/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 34-43 cores)</summary>

```
1794488205 34
1794488210 34
1794488215 34
1794488220 34
1794488225 34
1794488230 36
1794488235 36
1794488240 36
1794488245 36
1794488250 36
1794488256 36
1794488261 36
1794488266 36
1794488271 36
1794488276 36
1794488281 36
1794488286 36
1794488291 36
1794488296 36
1794488301 43
```
</details>

---

