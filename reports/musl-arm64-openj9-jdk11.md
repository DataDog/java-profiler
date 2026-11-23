---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 15:37:58 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 16 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1795465946 49
1795465951 49
1795465956 49
1795465961 49
1795465966 47
1795465971 47
1795465976 47
1795465981 47
1795465986 47
1795465991 47
1795465996 47
1795466001 47
1795466006 49
1795466011 49
1795466016 49
1795466021 49
1795466026 49
1795466031 49
1795466036 49
1795466041 49
```
</details>

---

