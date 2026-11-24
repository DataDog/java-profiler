---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 11:39:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1795537858 94
1795537863 94
1795537868 94
1795537873 94
1795537878 94
1795537883 94
1795537888 94
1795537893 94
1795537898 94
1795537903 94
1795537908 92
1795537913 92
1795537918 92
1795537923 92
1795537928 92
1795537933 92
1795537938 92
1795537943 92
1795537948 94
1795537953 94
```
</details>

---

