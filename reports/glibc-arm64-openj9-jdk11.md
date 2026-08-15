---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-15 05:47:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 10 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786787003 46
1786787008 46
1786787013 46
1786787018 46
1786787023 46
1786787028 46
1786787033 46
1786787038 48
1786787043 48
1786787048 48
1786787053 48
1786787058 48
1786787063 48
1786787068 48
1786787073 48
1786787078 48
1786787083 48
1786787088 48
1786787093 48
1786787098 48
```
</details>

---

