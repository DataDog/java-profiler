---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 08:47:50 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 14 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794922838 46
1794922843 46
1794922848 46
1794922853 46
1794922858 46
1794922863 46
1794922868 46
1794922873 46
1794922878 41
1794922883 41
1794922888 41
1794922893 41
1794922898 41
1794922903 41
1794922908 41
1794922913 41
1794922918 41
1794922923 41
1794922928 41
1794922933 41
```
</details>

---

