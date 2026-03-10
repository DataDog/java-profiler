---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-10 13:36:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 10 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 12 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (5 unique values: 38-46 cores)</summary>

```
1773163933 44
1773163938 44
1773163943 42
1773163948 42
1773163953 38
1773163958 38
1773163963 40
1773163968 40
1773163973 40
1773163978 42
1773163983 42
1773163988 42
1773163993 42
1773163998 42
1773164003 42
1773164008 42
1773164013 42
1773164018 42
1773164023 42
1773164028 42
```
</details>

---

