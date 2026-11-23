---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 10:10:51 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 39-41 cores)</summary>

```
1795446220 41
1795446225 41
1795446230 41
1795446235 41
1795446240 41
1795446245 41
1795446250 41
1795446255 39
1795446260 39
1795446265 39
1795446270 39
1795446275 39
1795446280 39
1795446285 39
1795446290 39
1795446295 39
1795446300 39
1795446305 39
1795446310 39
1795446315 39
```
</details>

---

