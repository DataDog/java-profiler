---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 20:52:54 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 42-64 cores)</summary>

```
1778546968 42
1778546973 42
1778546978 42
1778546983 42
1778546988 42
1778546993 42
1778546998 42
1778547003 42
1778547008 42
1778547013 42
1778547018 42
1778547023 42
1778547028 42
1778547033 64
1778547038 64
1778547043 64
1778547048 64
1778547053 64
1778547058 64
1778547063 64
```
</details>

---

