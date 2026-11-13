---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 16:23:59 EST

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 7 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (4 unique values: 8-18 cores)</summary>

```
1794604721 8
1794604726 8
1794604731 8
1794604736 8
1794604741 8
1794604746 8
1794604751 14
1794604756 14
1794604761 17
1794604766 17
1794604771 17
1794604777 17
1794604782 17
1794604787 17
1794604792 17
1794604797 17
1794604802 18
1794604807 18
1794604812 18
1794604817 18
```
</details>

---

