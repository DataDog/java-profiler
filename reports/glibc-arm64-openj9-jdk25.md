---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 13:11:28 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1793207249 46
1793207254 46
1793207259 46
1793207264 46
1793207269 46
1793207274 45
1793207279 45
1793207284 45
1793207289 45
1793207294 45
1793207299 45
1793207304 45
1793207309 45
1793207314 45
1793207319 45
1793207324 45
1793207329 46
1793207334 46
1793207339 46
1793207344 46
```
</details>

---

