---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 11:44:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 9 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (4 unique values: 87-94 cores)</summary>

```
1794847055 87
1794847060 87
1794847065 87
1794847070 89
1794847075 89
1794847080 94
1794847085 94
1794847090 94
1794847095 94
1794847100 94
1794847105 94
1794847110 94
1794847115 94
1794847120 94
1794847125 94
1794847130 94
1794847135 94
1794847140 94
1794847145 94
1794847150 94
```
</details>

---

