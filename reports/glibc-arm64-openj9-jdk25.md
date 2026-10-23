---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 10:56:47 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 9 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 19-41 cores)</summary>

```
1792767163 41
1792767168 41
1792767173 41
1792767178 41
1792767183 41
1792767188 41
1792767193 41
1792767198 36
1792767203 36
1792767208 36
1792767213 36
1792767218 36
1792767223 36
1792767228 36
1792767233 36
1792767238 36
1792767243 36
1792767249 36
1792767254 36
1792767259 19
```
</details>

---

