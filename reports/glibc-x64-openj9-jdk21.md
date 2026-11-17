---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 14:55:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1794945041 59
1794945046 59
1794945051 59
1794945056 59
1794945061 59
1794945066 59
1794945071 59
1794945077 59
1794945082 59
1794945087 59
1794945092 59
1794945097 59
1794945102 59
1794945107 59
1794945112 59
1794945117 61
1794945122 61
1794945127 61
1794945132 61
1794945137 61
```
</details>

---

