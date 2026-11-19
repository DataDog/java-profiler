---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 06:06:31 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (5 unique values: 38-51 cores)</summary>

```
1795085934 51
1795085939 49
1795085944 49
1795085949 49
1795085954 49
1795085959 49
1795085964 49
1795085969 44
1795085974 44
1795085979 44
1795085984 44
1795085989 44
1795085994 44
1795085999 44
1795086004 44
1795086009 44
1795086014 44
1795086019 44
1795086024 44
1795086029 44
```
</details>

---

