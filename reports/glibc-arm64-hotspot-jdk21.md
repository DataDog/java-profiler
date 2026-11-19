---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:54:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 11 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795114245 50
1795114250 50
1795114255 45
1795114260 45
1795114265 45
1795114270 45
1795114275 45
1795114280 45
1795114285 45
1795114290 45
1795114295 45
1795114300 45
1795114305 45
1795114310 45
1795114315 50
1795114320 50
1795114325 50
1795114330 50
1795114335 50
1795114340 50
```
</details>

---

