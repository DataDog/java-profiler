---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-24 15:44:30 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787600208 94
1787600213 94
1787600218 94
1787600223 94
1787600228 94
1787600233 94
1787600238 96
1787600243 96
1787600248 96
1787600253 96
1787600258 96
1787600263 96
1787600268 96
1787600273 96
1787600278 96
1787600283 96
1787600288 96
1787600293 96
1787600298 96
1787600303 96
```
</details>

---

