---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 00:00:37 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795409788 64
1795409793 64
1795409798 64
1795409803 64
1795409808 64
1795409813 64
1795409818 64
1795409823 64
1795409828 64
1795409833 64
1795409838 64
1795409843 64
1795409848 64
1795409853 64
1795409858 64
1795409863 64
1795409868 64
1795409873 64
1795409878 64
1795409883 64
```
</details>

---

