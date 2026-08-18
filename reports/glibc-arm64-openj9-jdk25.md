---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 10:31:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 9 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 15 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787063135 34
1787063140 34
1787063145 34
1787063150 34
1787063155 34
1787063160 34
1787063165 34
1787063170 34
1787063175 34
1787063180 34
1787063185 34
1787063190 34
1787063195 34
1787063200 34
1787063205 29
1787063210 29
1787063215 29
1787063220 29
1787063225 29
1787063230 29
```
</details>

---

