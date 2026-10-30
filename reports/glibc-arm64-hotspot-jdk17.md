---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 11:47:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 13 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (5 unique values: 43-48 cores)</summary>

```
1793374868 48
1793374873 47
1793374878 47
1793374883 47
1793374888 47
1793374893 45
1793374898 45
1793374903 43
1793374908 43
1793374913 43
1793374918 43
1793374923 43
1793374928 44
1793374933 44
1793374938 44
1793374943 44
1793374948 44
1793374953 44
1793374958 44
1793374963 44
```
</details>

---

