---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:47:08 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1794487337 48
1794487342 48
1794487347 48
1794487352 48
1794487357 48
1794487362 48
1794487367 48
1794487372 48
1794487377 48
1794487382 48
1794487387 48
1794487392 48
1794487397 48
1794487402 48
1794487407 48
1794487412 48
1794487417 48
1794487422 48
1794487427 40
1794487432 40
```
</details>

---

