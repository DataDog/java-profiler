---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:28:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 13 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795112536 50
1795112541 50
1795112546 50
1795112551 50
1795112556 50
1795112561 50
1795112566 50
1795112571 50
1795112576 50
1795112581 50
1795112586 50
1795112591 50
1795112596 50
1795112601 50
1795112606 50
1795112611 50
1795112616 50
1795112621 45
1795112626 45
1795112631 45
```
</details>

---

