---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:53:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1791470863 48
1791470868 48
1791470873 48
1791470878 48
1791470883 48
1791470888 48
1791470893 48
1791470898 48
1791470903 48
1791470908 48
1791470913 48
1791470918 48
1791470923 48
1791470928 48
1791470933 48
1791470938 40
1791470943 40
1791470948 40
1791470953 40
1791470958 40
```
</details>

---

