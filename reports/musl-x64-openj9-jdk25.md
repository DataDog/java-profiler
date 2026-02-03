---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 08:20:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 11 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 14.87/sec |
| Health Score | 929% |
| Threads | 12 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 25-28 cores)</summary>

```
1770124646 28
1770124651 28
1770124656 28
1770124661 28
1770124666 28
1770124671 28
1770124676 28
1770124681 28
1770124686 28
1770124691 28
1770124696 28
1770124701 25
1770124706 25
1770124711 25
1770124716 25
1770124721 25
1770124726 25
1770124732 25
1770124737 25
1770124742 25
```
</details>

---

