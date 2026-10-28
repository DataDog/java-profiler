---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:48:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 66-73 cores)</summary>

```
1793187852 69
1793187858 69
1793187863 69
1793187868 69
1793187873 69
1793187878 69
1793187883 71
1793187888 71
1793187893 71
1793187898 71
1793187903 71
1793187908 71
1793187913 71
1793187918 73
1793187923 73
1793187928 68
1793187933 68
1793187938 68
1793187943 68
1793187948 66
```
</details>

---

