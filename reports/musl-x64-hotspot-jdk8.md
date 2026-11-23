---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-23 05:22:28 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 48-57 cores)</summary>

```
1795429020 57
1795429025 57
1795429030 57
1795429035 48
1795429040 48
1795429045 57
1795429050 57
1795429055 57
1795429060 57
1795429065 57
1795429070 57
1795429075 55
1795429080 55
1795429085 55
1795429090 57
1795429095 57
1795429100 57
1795429105 57
1795429110 57
1795429115 57
```
</details>

---

