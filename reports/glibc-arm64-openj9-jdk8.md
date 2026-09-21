---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 08:08:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 224 |
| Sample Rate | 3.73/sec |
| Health Score | 233% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 7-11 cores)</summary>

```
1789992213 11
1789992218 11
1789992223 11
1789992228 11
1789992233 11
1789992238 11
1789992243 11
1789992248 11
1789992253 11
1789992258 11
1789992263 11
1789992268 11
1789992273 11
1789992278 11
1789992283 11
1789992288 11
1789992293 11
1789992298 7
1789992303 7
1789992308 7
```
</details>

---

