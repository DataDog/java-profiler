---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 06:29:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 317 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 63-66 cores)</summary>

```
1792578292 64
1792578297 64
1792578302 64
1792578307 64
1792578312 64
1792578317 64
1792578322 64
1792578327 64
1792578332 64
1792578337 64
1792578342 64
1792578347 64
1792578352 64
1792578357 64
1792578362 64
1792578367 64
1792578372 66
1792578377 66
1792578382 63
1792578387 63
```
</details>

---

