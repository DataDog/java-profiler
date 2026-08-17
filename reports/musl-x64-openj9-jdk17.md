---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-17 14:25:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 10 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 996 |
| Sample Rate | 16.60/sec |
| Health Score | 1038% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 66-94 cores)</summary>

```
1786990878 94
1786990883 86
1786990888 86
1786990893 86
1786990898 86
1786990903 86
1786990908 86
1786990913 86
1786990918 86
1786990923 86
1786990928 86
1786990933 86
1786990938 78
1786990943 78
1786990948 78
1786990953 78
1786990958 78
1786990963 78
1786990968 66
1786990973 66
```
</details>

---

