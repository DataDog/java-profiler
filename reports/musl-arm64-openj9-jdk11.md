---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-13 04:53:03 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1786610842 32
1786610847 32
1786610852 32
1786610857 32
1786610862 32
1786610867 32
1786610872 32
1786610877 32
1786610882 32
1786610887 32
1786610892 32
1786610897 32
1786610902 32
1786610907 32
1786610912 12
1786610917 12
1786610922 12
1786610927 12
1786610932 12
1786610937 12
```
</details>

---

