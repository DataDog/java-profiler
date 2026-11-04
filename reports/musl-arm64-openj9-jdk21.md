---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 16:24:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 36 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (3 unique values: 36-41 cores)</summary>

```
1793827202 41
1793827207 41
1793827212 41
1793827218 41
1793827223 41
1793827228 41
1793827233 39
1793827238 39
1793827243 39
1793827248 39
1793827253 39
1793827258 39
1793827263 39
1793827268 39
1793827273 41
1793827278 41
1793827283 36
1793827288 36
1793827293 36
1793827298 36
```
</details>

---

