---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 08:20:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 9 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 22-27 cores)</summary>

```
1770124419 27
1770124424 27
1770124429 27
1770124434 27
1770124439 27
1770124444 27
1770124449 27
1770124454 27
1770124459 27
1770124464 27
1770124469 25
1770124474 25
1770124479 22
1770124484 22
1770124489 22
1770124494 22
1770124499 22
1770124504 22
1770124509 24
1770124514 24
```
</details>

---

