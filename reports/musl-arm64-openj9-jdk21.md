---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:18:50 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795705987 33
1795705992 33
1795705997 33
1795706002 33
1795706007 33
1795706012 64
1795706017 64
1795706022 64
1795706027 64
1795706032 33
1795706037 33
1795706042 33
1795706047 33
1795706052 33
1795706058 33
1795706063 33
1795706068 33
1795706073 33
1795706078 33
1795706083 33
```
</details>

---

