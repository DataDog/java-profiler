---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 11:59:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 11 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1787154926 30
1787154931 30
1787154936 30
1787154941 30
1787154946 30
1787154951 29
1787154956 29
1787154961 29
1787154966 29
1787154971 29
1787154976 29
1787154981 29
1787154986 29
1787154991 29
1787154996 29
1787155001 30
1787155006 30
1787155011 32
1787155016 32
1787155021 32
```
</details>

---

