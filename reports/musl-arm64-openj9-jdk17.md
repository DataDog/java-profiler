---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:10:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 15-28 cores)</summary>

```
1795010745 15
1795010750 15
1795010756 15
1795010761 15
1795010766 15
1795010771 15
1795010776 15
1795010781 15
1795010786 15
1795010791 15
1795010796 15
1795010801 15
1795010806 15
1795010811 15
1795010816 15
1795010821 15
1795010826 15
1795010831 15
1795010836 28
1795010841 28
```
</details>

---

