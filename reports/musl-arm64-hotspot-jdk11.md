---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:29:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 11 |
| Allocations | 190 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 31-48 cores)</summary>

```
1794324176 48
1794324181 48
1794324186 48
1794324191 48
1794324196 48
1794324201 48
1794324206 48
1794324211 48
1794324216 48
1794324221 36
1794324226 36
1794324231 36
1794324236 36
1794324241 36
1794324246 36
1794324251 36
1794324256 36
1794324261 36
1794324266 36
1794324271 36
```
</details>

---

