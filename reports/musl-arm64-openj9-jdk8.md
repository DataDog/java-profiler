---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-15 03:56:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 23-53 cores)</summary>

```
1792050761 52
1792050766 52
1792050771 52
1792050776 52
1792050781 52
1792050786 52
1792050791 53
1792050796 53
1792050801 53
1792050806 53
1792050811 53
1792050816 53
1792050821 28
1792050826 28
1792050831 23
1792050836 23
1792050841 23
1792050846 23
1792050851 23
1792050856 23
```
</details>

---

