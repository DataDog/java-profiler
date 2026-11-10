---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 14:54:01 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
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
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794340104 48
1794340109 48
1794340114 48
1794340119 48
1794340124 47
1794340129 47
1794340134 47
1794340139 47
1794340144 47
1794340149 47
1794340154 47
1794340159 47
1794340164 47
1794340169 47
1794340174 47
1794340179 47
1794340184 48
1794340189 48
1794340194 48
1794340199 48
```
</details>

---

