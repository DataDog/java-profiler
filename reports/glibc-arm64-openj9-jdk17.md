---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-11 23:08:36 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 8 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1791774152 34
1791774157 34
1791774162 34
1791774167 34
1791774172 34
1791774177 34
1791774182 34
1791774187 34
1791774192 34
1791774197 34
1791774202 34
1791774207 34
1791774212 34
1791774217 34
1791774222 34
1791774227 34
1791774232 34
1791774237 34
1791774242 29
1791774247 29
```
</details>

---

