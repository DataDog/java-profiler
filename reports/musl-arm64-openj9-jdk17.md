---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-25 11:54:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1787672931 34
1787672936 34
1787672941 34
1787672946 34
1787672951 34
1787672956 34
1787672961 34
1787672966 34
1787672971 34
1787672976 34
1787672981 29
1787672986 29
1787672991 29
1787672996 29
1787673001 29
1787673006 29
1787673011 29
1787673016 29
1787673021 29
1787673026 29
```
</details>

---

