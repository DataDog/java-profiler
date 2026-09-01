---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-01 15:37:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788291112 64
1788291117 64
1788291122 64
1788291127 64
1788291132 64
1788291137 64
1788291142 64
1788291147 64
1788291152 64
1788291157 64
1788291162 64
1788291167 64
1788291172 64
1788291177 64
1788291182 64
1788291187 64
1788291192 62
1788291197 62
1788291202 62
1788291207 62
```
</details>

---

