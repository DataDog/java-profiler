---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:38:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (7 unique values: 79-85 cores)</summary>

```
1770125686 79
1770125691 79
1770125696 84
1770125701 84
1770125706 84
1770125711 84
1770125716 84
1770125721 84
1770125726 84
1770125731 82
1770125736 82
1770125741 82
1770125746 82
1770125751 81
1770125756 81
1770125761 81
1770125766 83
1770125771 83
1770125776 83
1770125781 83
```
</details>

---

