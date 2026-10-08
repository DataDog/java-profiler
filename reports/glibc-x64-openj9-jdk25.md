---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:53:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 22-32 cores)</summary>

```
1791470858 22
1791470863 22
1791470868 22
1791470873 22
1791470878 22
1791470883 22
1791470888 22
1791470893 22
1791470898 22
1791470903 22
1791470908 22
1791470913 22
1791470918 30
1791470923 30
1791470928 30
1791470933 30
1791470938 32
1791470943 32
1791470948 30
1791470953 30
```
</details>

---

