---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:07:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795618946 64
1795618951 64
1795618956 64
1795618961 64
1795618966 64
1795618971 47
1795618976 47
1795618981 47
1795618986 47
1795618991 47
1795618996 47
1795619001 47
1795619006 47
1795619011 47
1795619016 47
1795619021 47
1795619026 47
1795619031 47
1795619036 47
1795619041 47
```
</details>

---

