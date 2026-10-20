---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 17:52:27 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 7 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1051 |
| Sample Rate | 17.52/sec |
| Health Score | 1095% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1792532761 23
1792532766 23
1792532771 23
1792532776 28
1792532781 28
1792532786 28
1792532791 28
1792532796 28
1792532801 28
1792532806 28
1792532811 28
1792532816 28
1792532821 28
1792532826 28
1792532831 28
1792532836 28
1792532841 28
1792532846 28
1792532851 28
1792532856 28
```
</details>

---

