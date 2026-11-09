---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 11:10:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 11 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1794240222 48
1794240227 48
1794240232 48
1794240237 48
1794240242 48
1794240247 48
1794240252 48
1794240257 48
1794240262 48
1794240267 48
1794240272 48
1794240277 48
1794240282 48
1794240287 48
1794240292 46
1794240297 46
1794240302 46
1794240307 46
1794240312 41
1794240317 41
```
</details>

---

