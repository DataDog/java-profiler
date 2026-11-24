---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 05:51:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 15 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 17-33 cores)</summary>

```
1795517187 17
1795517192 17
1795517197 17
1795517202 17
1795517207 33
1795517212 33
1795517217 33
1795517222 33
1795517227 33
1795517232 33
1795517237 33
1795517242 33
1795517247 33
1795517252 33
1795517257 33
1795517262 33
1795517267 33
1795517272 33
1795517277 33
1795517282 33
```
</details>

---

