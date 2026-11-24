---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:59:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 31-35 cores)</summary>

```
1795532007 35
1795532012 35
1795532017 34
1795532022 34
1795532027 34
1795532032 34
1795532037 34
1795532042 34
1795532047 35
1795532052 35
1795532057 31
1795532062 31
1795532067 31
1795532072 31
1795532077 31
1795532082 31
1795532087 31
1795532092 31
1795532097 31
1795532102 31
```
</details>

---

