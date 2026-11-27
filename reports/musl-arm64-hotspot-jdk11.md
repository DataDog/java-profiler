---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 17:07:29 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 5 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795817040 64
1795817045 64
1795817050 64
1795817055 64
1795817060 64
1795817065 64
1795817070 64
1795817075 64
1795817080 64
1795817085 64
1795817090 64
1795817095 64
1795817100 64
1795817105 64
1795817110 64
1795817115 64
1795817120 64
1795817125 64
1795817130 64
1795817135 64
```
</details>

---

