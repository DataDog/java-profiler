---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:28:35 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1028 |
| Sample Rate | 17.13/sec |
| Health Score | 1071% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1790094072 49
1790094077 49
1790094082 49
1790094087 49
1790094092 49
1790094097 49
1790094102 49
1790094107 49
1790094112 49
1790094117 49
1790094122 49
1790094127 49
1790094132 49
1790094137 49
1790094142 49
1790094147 49
1790094152 49
1790094157 49
1790094162 49
1790094167 49
```
</details>

---

