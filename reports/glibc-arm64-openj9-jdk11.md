---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 16:22:25 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 10 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 43-44 cores)</summary>

```
1790713114 44
1790713119 44
1790713124 44
1790713129 44
1790713134 44
1790713139 44
1790713144 44
1790713149 44
1790713154 44
1790713159 44
1790713164 44
1790713169 43
1790713174 43
1790713179 43
1790713184 43
1790713189 43
1790713194 43
1790713199 43
1790713204 43
1790713209 43
```
</details>

---

