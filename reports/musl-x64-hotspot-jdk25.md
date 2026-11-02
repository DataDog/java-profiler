---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 11:02:24 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 61-65 cores)</summary>

```
1793635035 61
1793635040 61
1793635045 61
1793635050 61
1793635055 61
1793635060 61
1793635065 61
1793635070 61
1793635075 63
1793635080 63
1793635085 63
1793635090 65
1793635095 65
1793635100 65
1793635105 65
1793635110 65
1793635116 65
1793635121 65
1793635126 65
1793635131 65
```
</details>

---

