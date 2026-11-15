---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 08:56:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 10 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794750706 29
1794750711 29
1794750716 29
1794750721 29
1794750726 29
1794750731 29
1794750736 29
1794750741 29
1794750746 29
1794750751 29
1794750756 29
1794750761 29
1794750766 29
1794750771 29
1794750776 34
1794750781 34
1794750786 34
1794750791 34
1794750796 34
1794750801 34
```
</details>

---

